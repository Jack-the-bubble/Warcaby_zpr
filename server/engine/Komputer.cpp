#include "Komputer.h"
using namespace std;


Komputer::Komputer(int graczID_)
{
	graczID = graczID_;
	

}


Komputer::~Komputer()
{
}

int Komputer::getID()
{
	return graczID;
}

/**
	Funkcja wywolywana przy przekazaniu ruchu dla gracza. 
	Kopiuje aktualna zawartosc planszy
	Wywoluje algorytm znajdujacy najlepsze dla gracza posuniecie

	@param plansza[8][8] aktualny stan planszy gry
*/
void Komputer::update(const int plansza[8][8])
{
	bestMove.ID = 0;

	

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			boardCopy[i][j] = plansza[i][j];
			if (boardCopy[i][j] == graczID || boardCopy[i][j] == 2*graczID) ++myCnt;
			else if (boardCopy[i][j] == -graczID || boardCopy[i][j] == -2*graczID) ++oponentCnt;
		}
	}

	alfabetaFirst(depthMax, -1000000, 1000000);

	if(bestMove.ID != 0) makeMove(bestMove);
}


/**
	Funkcja sprawdza czy dla danego pionka czy jest mozliwy ruch

	@param ID ID gracza wykonujacego ruch w danym posunieciu.
	@return czy mozliwy ruch dla aktualnie rozpatrywanego pionka o wsp(w_,k_) w aktualnym posunieciu
*/

bool Komputer::possibleMoves(int ID)
{
	bool moves = false;


	if (biciePossible)
	{
		if (boardCopy[w_][k_] == ID) moves = bicie(ID, w_, k_);
		else if (boardCopy[w_][k_] == 2*ID) moves = bicieDamka(ID, w_, k_);
	}

	else  //jesli nie ma bicia
	{
		if (czyRuchBezBicia(ID, 1, k_, w_) || czyRuchBezBicia( ID, -1, k_, w_) || isKingMoveBack( ID, 1, k_, w_) || isKingMoveBack(ID, -1, k_, w_))
		{
			moves = true;
		}
	}

	return moves;
}



/**
	Pierwsze wywolanie algorytmu minimax z odcinaniem alfa-beta. Funkcja odpowiedzialna jest
	za przeprowadzenie pierwszego z ruchow komputera i wybor najlepszego.
	Nastepne ruchy graczy wywolywane sa rekurencyjnie - komputer jest graczem maksymalizujacym wynik
	natomiast przeciwnik - minimalizujacym.
	Parametry alfa oraz beta mowia o aktualnie znalezionej korzysci z danego ruchu dla obydwu graczy.
	Najlepszy znaleziony wynik zapisywany jest do skladowej bestMove

	@param depth Glebokosc przeszukiwania drzewa gry.
	@param alpha Najlepszy wynik dla gracza maksymalizujacego.
	@param beta Najlepszy wynik dla gracza minimalizujacego.
	@return Heurystyka po wykonaniu najlepszego posuniecia dla gracza
			wykonujacego ruch w danej chwili.
*/

int Komputer::alfabetaFirst(int depth, int alpha, int beta)
{
	
	czyBicie(graczID);
	int pos = 0;
	int nextColumn[12];
	int nextRow[12];
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			k_ = j;
			w_ = i;
			if (boardCopy[i][j] == graczID || boardCopy[i][j] == 2*graczID)
			{
				if (possibleMoves(graczID))
				{
					nextColumn[pos] = k_;
					nextRow[pos] = w_;
					++pos;
				}
			}
		}
	}
	
	if (wygrana() != 0 || depth == 0 || pos == 0) return markBrd();  //koniec galezi ocen stan

	int ID = graczID;

	for (int i = 0; i < pos; ++i)
	{
		k_ = nextColumn[i];  //root
		w_ = nextRow[i];  //root
		std::list<Move> nextMoves;
		if (boardCopy[w_][k_] == ID)
		{
			nextMoves = nextPositions(ID, 1, k_, w_); //w prawo
			nextMoves.splice(nextMoves.end(), nextPositions(ID, -1, k_, w_)); //w lewo
		}
		else if (boardCopy[w_][k_] == 2 * ID)
		{
			nextMoves = nextKingPositions(ID, 1, k_, w_); //w prawo
			nextMoves.splice(nextMoves.end(), nextKingPositions(ID, -1, k_, w_)); //w lewo
		}
		

		if (pos == 1 && nextMoves.size() == 1)
		{
			bestMove = nextMoves.front();
			return 0;
		}
		while (!nextMoves.empty())
		{
			makeMove(nextMoves.front());

			int result = alfabeta(depth - 1, alpha, beta, -ID);
			if (alpha < result) {
				alpha = result;
				bestMove = nextMoves.front();
			}
			rollBackMove(nextMoves.front());
			nextMoves.pop_front();
		}
			
	}
	return 0;
}

/**
	Funkcja odpowiedzialna za sprawdzanie kazdego wierzcholka drzewa gry oraz
	realizacje odcinania alfa-beta. Wywolywana jest rekurencyjnie dla kazdego stanu potomnego.
	Komputer jest graczem maksymalizujacym wynik natomiast przeciwnik - minimalizujacym.
	Wywolywana jest rekurencyjnie az do momentu znalezienia stanu terminalnego lub koncowego albo uzyskania
	zadanej glebokosci przeszukiwania.
	Parametry alfa oraz beta mowia o aktualnie znalezionej korzysci z danego ruchu dla obydwu graczy.
	W celu wywolania funkcji konieczne jest takze podanie ID gracza wykonujacego w danej chwili ruch oraz
	numer kolumny i wiersza w których umieszczony zostal zeton w poprzednim ruchu (w celu efektywnego sprawdzenia
	czy po ruchu nie wystapil stan terminalny).


	@param depth Glebokosc przeszukiwania drzewa gry.
	@param alpha Najlepszy wynik dla gracza maksymalizujacego.
	@param beta Najlepszy wynik dla gracza minimalizujacego.
	@param ID ID gracza wykonujacego ruch w danym posunieciu.


	@return Heurystyka po wykonaniu najlepszego posuniecia dla gracza
			wykonujacego ruch w danej chwili.
*/
int Komputer::alfabeta(int depth, int alpha, int beta, int ID)
{	
	biciePossible = false;

	czyBicie(ID);
	int nextColumn[12];
	int nextRow[12];
	int pos = 0;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			k_ = j;
			w_ = i;
			if (boardCopy[i][j] == ID)
			{
				if (possibleMoves(ID))
				{
					nextColumn[pos] = k_;
					nextRow[pos] = w_;
					++pos;
				}
			}
		}
	}



	if (depth == 0 || pos == 0 || wygrana() != 0 ) return markBrd();  //koniec galezi ocen stan

	if (ID == graczID)
	{
		for (int i = 0; i < pos; ++i)
		{
			k_ = nextColumn[i];  //root
			w_ = nextRow[i];  //root

			std::list<Move> nextMoves = nextPositions(ID, 1, k_, w_); //w prawo
			nextMoves.splice(nextMoves.end(), nextPositions(ID, -1, k_, w_)); //w lewo


			while (!nextMoves.empty())
			{
				makeMove(nextMoves.front());

				int result = alfabeta(depth - 1, alpha, beta, -ID);
				rollBackMove(nextMoves.front());
				nextMoves.pop_front();
				if (alpha < result) {
					alpha = result;
				}
				if (alpha >= beta)
					return beta;
			}
		}
	return alpha;
	}

	else   //gdy ID przeciwnika
	{
		for (int i = 0; i < pos; ++i)
		{
			k_ = nextColumn[i];  //root
			w_ = nextRow[i];  //root

			std::list<Move> nextMoves = nextPositions(ID, 1, k_, w_); //w prawo
			nextMoves.splice(nextMoves.end(), nextPositions(ID, -1, k_, w_)); //w lewo


			while (!nextMoves.empty())
			{
				makeMove(nextMoves.front());

				int result = alfabeta(depth - 1, alpha, beta, -ID);
				rollBackMove(nextMoves.front());
				nextMoves.pop_front();
				if (beta > result) {
					beta = result;
				}
				if (alpha >= beta)
					return alpha;
			}
		}
		return beta;
	}
}

/**
	Sprawdza czy plansza w stanie terminalnym

	@return 1 gdy wygrana gracza, -1 gdy wygrana oponenta, 0 gdy brak rozstrzygniecia
*/
int Komputer::wygrana()
{
	
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (graczID * boardCopy[i][j] >= 1 ) cnt1++;
			if (graczID * boardCopy[i][j] <= -1) cnt2++;
		}
	}
	if (cnt1 == 0) return 1;
	if (cnt2 == 0) return -1;
	return 0;
}

/**
	Funkcja czy dla danego pionka czy jest mozliwe bicie w dowolnym kierunku.

	@param ID ID gracza wykonujacego ruch w danym posunieciu.
	@param wiersz wiersz aktualnie rozpatrywanego pionka
	@param kol kolumna aktualnie rozpatrywanego pionka
	@return czy mozliwe bicie dla pionka o wsp(wiersz,kol) w aktualnym posunieciu
*/
bool Komputer::bicie(int ID, int wiersz, int kol)
{


	if (kol-2 >= 0 && (wiersz + ID * 2) >= 0 && (wiersz + ID * 2) < SIZE)
	{
		if (boardCopy[wiersz + ID * 1][kol - 1] == -(ID) || boardCopy[wiersz + ID * 1][kol - 1] == -(2*ID))
		{
			if (boardCopy[wiersz + ID * 2][kol - 2] == 0)
			{
				return true;
			}
		}
	}

	if (kol+2 < SIZE && (wiersz + ID * 2) >= 0 && (wiersz + ID * 2) < SIZE)
	{
		if (boardCopy[wiersz + ID * 1][kol + 1] == -(ID) || boardCopy[wiersz + ID * 1][kol + 1] == -(2*ID))
		{
			if (boardCopy[wiersz + ID * 2][kol + 2] == 0)
			{
				return true;
			}

		}
	}


	//bicia do tylu
	if (kol - 2 >= 0 && (wiersz - ID * 2) >= 0 && (wiersz - ID * 2) < SIZE)
	{
		if (boardCopy[wiersz - ID * 1][kol - 1] == -(ID) || boardCopy[wiersz - ID * 1][kol - 1] == -(2*ID))
		{
			if (boardCopy[wiersz - ID * 2][kol - 2] == 0)
			{
				return true;
			}
		}
	}

	if (kol+2 < SIZE && (wiersz - ID * 2) >= 0 && (wiersz - ID * 2) < 8)
	{
		if (boardCopy[wiersz - ID * 1][kol + 1] == -(ID) || boardCopy[wiersz - ID * 1][kol + 1] == -(2*ID))
		{
			if (boardCopy[wiersz - ID * 2][kol + 2] == 0)
			{
				return true;
			}
		}
	}

	return false;
}

/**
	Funkcja czy dla danej damki czy jest mozliwe bicie w dowolnym kierunku.

	@param ID ID gracza wykonujacego ruch w danym posunieciu.
	@param wiersz wiersz aktualnie rozpatrywanego pionka
	@param kol kolumna aktualnie rozpatrywanego pionka
	@return czy mozliwe bicie dla pionka o wsp(wiersz,kol) w aktualnym posunieciu
*/
bool Komputer::bicieDamka(int ID, int wiersz, int kol)
{


	if (kol - 2 >= 0 && (wiersz + ID * 2) >= 0 && (wiersz + ID * 2) < SIZE)
	{
		for (int i = 0; (kol - 2 - i >= 0) && (wiersz + ID*( 2 + i ) >=0 && (wiersz + ID * (2 + i) < SIZE)); ++i)
		{
			if (boardCopy[wiersz + ID * ( 1 + i)][kol - 1 - i] == -(ID) || boardCopy[wiersz + ID *(1 + i)][kol - 1 - i] == -2*(ID))
			{
				if (boardCopy[wiersz + ID *(2 + i)][kol - 2 - i] == 0)
				{
					return true;
				}
			}

		}
		
	}

	if (kol + 2 < SIZE && (wiersz + ID * 2) >= 0 && (wiersz + ID * 2) < SIZE)
	{
		for (int i = 0; (kol + 2 + i < SIZE) && (wiersz + ID * (2 + i) >= 0 && (wiersz + ID * (2 + i) < SIZE)); ++i)
		{
			if (boardCopy[wiersz + ID * (1 + i)][kol + 1 + i] == -(ID) || boardCopy[wiersz + ID * (1 + i)][kol + 1 + i] == -2 * (ID))
			{
				if (boardCopy[wiersz + ID * (2 + i)][kol + 2 + i] == 0)
				{
					return true;
				}
			}

		}
		
	}


	//bicia do tylu
	if (kol - 2 >= 0 && (wiersz - ID * 2) >= 0 && (wiersz - ID * 2) < SIZE)
	{
		for (int i = 0; (kol - 2 - i >= 0) && (wiersz - ID * (2 + i) >= 0 && (wiersz - ID * (2 + i) < SIZE)); ++i)
		{
			if (boardCopy[wiersz - ID * (1 + i)][kol - 1 - i] == -(ID) || boardCopy[wiersz - ID * (1 + i)][kol - 1 - i] == -2 * (ID))
			{
				if (boardCopy[wiersz - ID * (2 + i)][kol - 2 - i] == 0)
				{
					return true;
				}
			}

		}
	}

	if (kol + 2 < SIZE && (wiersz - ID * 2) >= 0 && (wiersz - ID * 2) < 8)
	{
		for (int i = 0; (kol + 2 + i < SIZE) && (wiersz - ID * (2 + i) >= 0 && (wiersz - ID * (2 + i) < SIZE)); ++i)
		{
			if (boardCopy[wiersz - ID * (1 + i)][kol + 1 + i] == -(ID) || boardCopy[wiersz - ID * (1 + i)][kol + 1 + i] == -2 * (ID))
			{
				if (boardCopy[wiersz - ID * (2 + i)][kol + 2 + i] == 0)
				{
					return true;
				}
			}

		}
	}

	return false;
}

/**
	Funkcja sprawdza przymus bicia w danym posunieciu.
	Dla kazdego pionka gracza wykonujacego ruch sprawdza czy jest mozliwe bicie
	jesli chociaz jeden ma mozliwe bicie to zwraca true

	@param ID ID gracza wykonujacego ruch w danym posunieciu.
	@return czy jest przymus bicia w aktualnym posunieciu
*/
bool Komputer::czyBicie(int ID )
{
	biciePossible = false;


	bool pom = false;
	//sprawdzenie czy jest przymus bicia
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if(boardCopy[i][j] == ID)	pom = bicie(ID, i, j);  //bicie pionka
			if (boardCopy[i][j] == 2 * ID) pom = bicieDamka(ID, i, j); //bicie damki
			if (pom)
			{
				biciePossible = true;
				break;
			}
		}
	}
	
	return biciePossible;
}

/**
	Wylicza heurystyke oceniajaca stan planszy.
	Dodatnia oznacza korzystne ustawienie dla gracza a ujemna negatywne.

	@return heurystyka oceniajaca
*/

int Komputer::markBrd()
{
	int myCnt2 = 0;
	int oponentCnt2 = 0;
	
	int ocena = 0;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (boardCopy[i][j] == graczID)
			{
				ocena += WAGA_PIONKA;
				++myCnt2;
			}
			if (boardCopy[i][j] == -graczID)
			{
				ocena += -WAGA_PIONKA;
				++oponentCnt2;
			}
				
			if (boardCopy[i][j] == 2 * graczID)
			{
				ocena += WAGA_DAMKI;
				++myCnt2;
			}
			if (boardCopy[i][j] == -2 * graczID)
			{
				ocena += -WAGA_DAMKI;
				++oponentCnt2;
			}

			if (graczID == 1)
			{
				if (boardCopy[i][j] == graczID || boardCopy[i][j] == 2 * graczID)
				{
					if (i >= 0 && i < 2) ocena += 1;	//poziom 1
					else if (i >= 2 && i < 4) ocena += 2;	//poziom 2
					else if (i >= 4 && i < 6) ocena += 3;	//poziom 3
					else if (i >= 6 && i < 8) ocena += 4;	//poziom 4
					if (i == 7) ocena += 20;
				}
			}

			if (graczID == -1)
			{
				if (boardCopy[i][j] == graczID || boardCopy[i][j] == 2 * graczID)
				{
					if (i >= 6  && i < 8) ocena += 1;	//poziom 1
					else if (i >= 4 && i < 6) ocena += 2;	//poziom 2
					else if (i >= 2 && i < 4) ocena += 3;	//poziom 3
					else if (i >= 0 && i < 2) ocena += 4;	//poziom 4
					if (i == 0) ocena += 20;
				}
			}
		}
	}

	ocena += 100 * (oponentCnt - oponentCnt2); //gratyfikacja zbic
	ocena += -100 * (myCnt - myCnt2); //unikanie tracenia pionkow


	return ocena;
}

/**
	Znajduje wszystkie mozliwe ruchy dla aktualnie rozpatrywanego pionka i zapisuje je do listy. 
	Wywoluje sie rekurancyjnie w celu sprawdzenia mozliwych bic wielokrotnych.

	@param ID ID gracza wykonujacego ruch w danym posunieciu.
	@param dir okresla kierunek ruchu ;1 ruch w prawo ;-1 ruch w lewo
	@param k kolumna aktualnie rozpatrywanego pionka
	@param w wiersz aktualnie rozpatrywanego pionka
	@return lista mozliwych posuniec z pionka o wspolrzednych (w,k)
*/

std::list<Move> Komputer::nextPositions(int ID, int dir, int k, int w) 
{
	std::list<Move> myMoves;
	if (!biciePossible)
	{
		if (czyRuchBezBicia(ID, dir, k, w))  
		{
			Move newMove(w , k, w + ID, k + dir, ID);
			if ((ID == 1 && w+ID == SIZE - 1) || (ID == -1 && w + ID == 0))
			{
				newMove.kingCreate = true;
				newMove.createKing();  //stworzenie damki
			}
			myMoves.push_back(newMove);
		}
	}
	else {

		if (boardCopy[w][k] == ID && k + dir * 2 < SIZE && k + dir * 2 >= 0 && w + ID * 2 >= 0 && w + ID * 2 < SIZE
			&& boardCopy[w + ID * 2][k + dir * 2] == 0 && (boardCopy[w + ID * 1][k + dir * 1] == -ID || boardCopy[w + ID * 1][k + dir * 1] == -2*ID))    //bicie w przod
		{
			
			Move newMove(w, k, w + 2 * ID, k + 2 * dir, ID, w + ID * 1, k + dir * 1);

			if ((ID == 1 && w == SIZE - 1) || (ID == -1 && w == 0))
			{
				newMove.createKing();  //stworzenie damki
				newMove.kingCreate = true;
			}
			myMoves.push_back(newMove);
			makeMove(newMove);

			int lastsize = myMoves.size();

			std::list<Move> nextList;

			if (!(nextList = nextPositions(ID, 1, k + dir * 2, w + ID * 2)).empty())
				myMoves.splice(myMoves.end(), nextList);
			if (!(nextList = nextPositions(ID, -1, k + dir * 2, w + ID * 2)).empty())
				myMoves.splice(myMoves.end(), nextList);

			
			
			rollBackMove(newMove);
			if (lastsize == myMoves.size())
			{
				return myMoves;
			}
			else
			{
				bool king = false;
				for (list<Move>::iterator it = myMoves.begin(); it != myMoves.end(); it++)
				{
					
					if ((*it).kingCreate) king = true;
					if (king)
					{
						(*it).kingCreate = true;
						(*it).createKing();
					}
					(*it).from[0] = w;
					(*it).from[1] = k;
					(*it).addCaptured(w + ID * 1, k + dir * 1);
				}
				for (int i = 0; i < lastsize; ++i) myMoves.pop_front();
			}
		}

		if (boardCopy[w][k] == ID && k + dir * 2 < SIZE && k + dir * 2 >= 0 && w - ID * 2 >= 0 && w - ID * 2 < SIZE
			&& boardCopy[w - ID * 2][k + dir * 2] == 0 && (boardCopy[w - ID * 1][k + dir * 1] == -ID || boardCopy[w - ID * 1][k + dir * 1] == -2*ID))    //bicie w tyl
		{
			
			Move newMove(w, k, w - 2 * ID, k + 2 * dir, ID, w - ID * 1, k + dir * 1);
			if ((ID == 1 && w == SIZE - 1) || (ID == -1 && w == 0))
			{
				newMove.createKing();  //stworzenie damki
				newMove.kingCreate = true;
			}
			myMoves.push_back(newMove);
			makeMove(newMove);

			int lastsize = myMoves.size();

			std::list<Move> nextList;

			if (!(nextList = nextPositions(ID, 1, k + dir * 2, w - ID * 2)).empty())
				myMoves.splice(myMoves.end(), nextList);
			if (!(nextList = nextPositions(ID, -1, k + dir * 2, w - ID * 2)).empty())
				myMoves.splice(myMoves.end(), nextList);



			rollBackMove(newMove);
			if (lastsize == myMoves.size())
			{
				return myMoves;
			}
			else
			{
				bool king = false;
				for (list<Move>::iterator it = myMoves.begin(); it != myMoves.end(); it++)
				{

					if ((*it).kingCreate) king = true;
					if (king)
					{
						(*it).kingCreate = true;
						(*it).createKing();
					}
					(*it).from[0] = w;
					(*it).from[1] = k;
					(*it).addCaptured(w - ID * 1, k + dir * 1);
				}
				for (int i = 0; i < lastsize; ++i) myMoves.pop_front();
			}
		}

	}

	return myMoves;
}


/**
	Znajduje wszystkie mozliwe ruchy dla aktualnie rozpatrywanej damki i zapisuje je do listy.
	Wywoluje sie rekurancyjnie w celu sprawdzenia mozliwych bic wielokrotnych.

	@param ID ID gracza wykonujacego ruch w danym posunieciu.
	@param dir okresla kierunek ruchu ;1 ruch w prawo ;-1 ruch w lewo
	@param k kolumna aktualnie rozpatrywanego pionka
	@param w wiersz aktualnie rozpatrywanego pionka
	@return lista mozliwych posuniec damki o wspolrzednych (w,k)
*/
std::list<Move> Komputer::nextKingPositions(int ID, int dir, int k, int w)
{
	std::list<Move> myMoves;
	if (!biciePossible)
	{
		if (czyRuchBezBicia(ID, dir, k, w))
		{
			for (int i = 0; w + ID * (1 + i) >= 0 && w + ID * (1 + i) < SIZE && k + dir * (1 + i) >= 0 && k + dir * (1 + i) < SIZE && boardCopy[w + ID * (1 + i)][k + dir * (1 + i)] == 0; ++i)
			{
				Move newMove(w, k, w + ID * (1 + i), k + dir * (1 + i), 2 * ID);
				myMoves.push_back(newMove);
			}
		}

		if (isKingMoveBack(ID, dir, k, w))
		{
			for (int i = 0; w - ID * (1 + i) >= 0 && w - ID * (1 + i) < SIZE && k + dir * (1 + i) >= 0 && k + dir * (1 + i) < SIZE && boardCopy[w - ID * (1 + i)][k + dir * (1 + i)] == 0; ++i)
			{
				Move newMove(w, k, w - ID * (1 + i), k + dir * (1 + i), 2 * ID);
				myMoves.push_back(newMove);
			}

		}

	}
	else {

		if (boardCopy[w][k] == 2 * ID && k + dir * 2 < SIZE && k + dir * 2 >= 0 && w + ID * 2 >= 0 && w + ID * 2 < SIZE)    //bicie w przod
		{
			//opis warunkow po kolei: kolumna po biciu wieksza rowna 0; kolumna po biciu mniejsza od 8;  wiersz bo biciu wiekszy rowny 0; wiersz po biciu mniejszy od 8
			//pole puste az do znalezienia bicia chyba ze i == 0
			for (int i = 0; (k + dir * (2 + i) >= 0) && (k + dir * (2 + i) < SIZE) && (w + ID * (2 + i) >= 0 && (w + ID * (2 + i) < SIZE))
				&& (boardCopy[w + ID * i][k + dir * i] == 0 || i == 0); ++i)
			{
				//znalezienie pionka do bicia na nastepnym polu
				if (boardCopy[w + ID * (1 + i)][k + dir*(1 + i)] == -(ID) || boardCopy[w + ID * (1 + i)][k + dir*(1 + i)] == -2 * (ID))
				{
					//opis warunkow po kolei: j-ty wiersz za pionkiem >= 0 oraz <8; j-ta kolumna za pionkiem >=0 oraz <8; j-te miejsce za pionkiem puste 
					for (int j = 0; w + ID * (2 + i + j) >= 0 && w + ID * (2 + i + j) < SIZE && k + dir * (2 + i + j) >= 0
						&& k + dir * (2 + i + j) < SIZE && boardCopy[w + ID * (2 + i + j)][k + dir * (2 + i + j)] == 0; ++j)
					{
						Move newMove(w, k, w + ID * (2 + i + j), k + dir * (2 + i + j), 2 * ID, w + ID * (1 + i), k + dir * (1 + i));
						myMoves.push_back(newMove);
						makeMove(newMove);

						int lastsize = myMoves.size();

						std::list<Move> nextList;

						if (!(nextList = nextKingPositions(ID, 1, k + dir * (2 + i + j), w + ID * (2 + i + j))).empty())
							myMoves.splice(myMoves.end(), nextList);
						if (!(nextList = nextKingPositions(ID, -1, k + dir * (2 + i + j), w + ID * (2 + i + j))).empty())
							myMoves.splice(myMoves.end(), nextList);


						rollBackMove(newMove);
						if (lastsize == myMoves.size())
						{
							return myMoves;
						}
						else
						{
							for (list<Move>::iterator it = myMoves.begin(); it != myMoves.end(); it++)
							{
								(*it).from[0] = w;
								(*it).from[1] = k;
								(*it).addCaptured(w + ID * (1 + i), k + dir * (1 + i));
							}
							for (int i = 0; i < lastsize; ++i) myMoves.pop_front();
						}

					}
				}
			}

			if (boardCopy[w][k] == 2 * ID && k + dir * 2 < SIZE && k + dir * 2 >= 0 && w - ID * 2 >= 0 && w - ID * 2 < SIZE)    //bicie w tyl
			{
				//opis warunkow po kolei: kolumna po biciu wieksza rowna 0; kolumna po biciu mniejsza od 8;  wiersz bo biciu wiekszy rowny 0; wiersz po biciu mniejszy od 8
				//pole puste az do znalezienia bicia chyba ze i == 0
				for (int i = 0; (k + dir * (2 + i) >= 0) && (k + dir * (2 + i) < SIZE) && (w - ID * (2 + i) >= 0 && (w - ID * (2 + i) < SIZE))
					&& (boardCopy[w - ID * i][k + dir * i] == 0 || i == 0); ++i)
				{
					//znalezienie pionka do bicia na nastepnym polu
					if (boardCopy[w - ID * (1 + i)][k + dir*(1 + i)] == -(ID) || boardCopy[w - ID * (1 + i)][k + dir*(1 + i)] == -2 * (ID))
					{
						//opis warunkow po kolei: j-ty wiersz za pionkiem >= 0 oraz <8; j-ta kolumna za pionkiem >=0 oraz <8; j-te miejsce za pionkiem puste 
						for (int j = 0; w - ID * (2 + i + j) >= 0 && w - ID * (2 + i + j) < SIZE && k + dir * (2 + i + j) >= 0
							&& k + dir * (2 + i + j) < SIZE && boardCopy[w - ID * (2 + i + j)][k + dir * (2 + i + j)] == 0; ++j)
						{
							Move newMove(w, k, w - ID * (2 + i + j), k + dir * (2 + i + j), 2 * ID, w - ID * (1 + i), k + dir * (1 + i));
							myMoves.push_back(newMove);
							makeMove(newMove);

							int lastsize = myMoves.size();

							std::list<Move> nextList;

							if (!(nextList = nextKingPositions(ID, 1, k + dir * (2 + i + j), w - ID * (2 + i + j))).empty())
								myMoves.splice(myMoves.end(), nextList);
							if (!(nextList = nextKingPositions(ID, -1, k + dir * (2 + i + j), w - ID * (2 + i + j))).empty())
								myMoves.splice(myMoves.end(), nextList);


							rollBackMove(newMove);
							if (lastsize == myMoves.size())
							{
								return myMoves;
							}
							else
							{
								for (list<Move>::iterator it = myMoves.begin(); it != myMoves.end(); it++)
								{
									(*it).from[0] = w;
									(*it).from[1] = k;
									(*it).addCaptured(w - ID * (1 + i), k + dir * (1 + i));
								}
								for (int i = 0; i < lastsize; ++i) myMoves.pop_front();
							}

						}
					}
				}
			}
		}
	}

	return myMoves;
}

/**
	Sprawdza mozliwosc najprostszego ruchu bez bicia w kierunku okreslonym przez dir.

	@param ID ID gracza wykonujacego ruch w danym posunieciu.
	@param dir okresla kierunek ruchu ;1 ruch w prawo ;-1 ruch w lewo
	@param k kolumna aktualnie rozpatrywanego pionka
	@param w wiersz aktualnie rozpatrywanego pionka
	@return true jesli jest mozliwy ruch
*/
bool Komputer::czyRuchBezBicia( int ID, int dir, int k, int w)
{
	return ((boardCopy[w][k] == ID || boardCopy[w][k] == 2*ID) && k + dir * 1 < SIZE && k + dir * 1 >= 0 && boardCopy[w + ID * 1][k + dir * 1] == 0 
		&& w + ID >= 0 && w + ID < SIZE);
}

/**
	Sprawdza mozliwosc ruchu bez bicia do tylu dla damki

	@param ID ID gracza wykonujacego ruch w danym posunieciu.
	@param dir okresla kierunek ruchu ;1 ruch w prawo ;-1 ruch w lewo
	@param k kolumna aktualnie rozpatrywanego pionka
	@param w wiersz aktualnie rozpatrywanego pionka
	@return true jesli jest mozliwy ruch
*/
bool Komputer::isKingMoveBack(int ID, int dir, int k, int w)
{
	return ((boardCopy[w][k] == 2*ID ) && k + dir * 1 < SIZE && k + dir * 1 >= 0 && boardCopy[w - ID * 1][k + dir * 1] == 0 && (w - ID*1) >= 0 && (w - ID) < SIZE);
}

/**
	Wykonuje ruch na skladowej boardCopy okreslony przez move 

	@param move ruch do wykonania
*/
void Komputer::makeMove(Move move)
{
	
	boardCopy[move.from[0]][move.from[1]] = 0;
	boardCopy[move.to[0]][move.to[1]] = move.ID;

	vector<int>::iterator it;
	vector<int>::iterator it2;
	for (it = move.capturedRow.begin(), it2 = move.capturedCol.begin(); it != move.capturedRow.end(); it++, it2++)
	{
		boardCopy[*it][*it2] = 0;  
	}
	
}

/**
	Cofa ruch na skladowej boardCopy okreslony przez move

	@param move ruch do cofniecia
*/
void Komputer::rollBackMove(Move move)
{
	if(move.kingCreate) 
		boardCopy[move.from[0]][move.from[1]] = move.ID / 2;
	else boardCopy[move.from[0]][move.from[1]] = move.ID;
	boardCopy[move.to[0]][move.to[1]] = 0;

	vector<int>::iterator it;
	vector<int>::iterator it2;
	for (it = move.capturedRow.begin() , it2 = move.capturedCol.begin(); it != move.capturedRow.end(); it++ , it2++)
	{
		boardCopy[*it][*it2] = -(move.ID);  
	}
}

/**
	Zwraca najlepszy ruch wybrany przez koputer w trakcie realizacji algorytmu
	minimax z odcinaniem alfa-beta.

	@return move do wykonania na glownej planszy gry
*/
Move Komputer::getBestMove()
{
	return bestMove;
}