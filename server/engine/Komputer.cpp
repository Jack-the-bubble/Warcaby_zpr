#include "Komputer.h"
using namespace std;


Komputer::Komputer()
{
	graczID =-1;
	myCnt = oponentCnt = 12;

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
	myCnt = 0;
	oponentCnt = 0;


	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
		{
			boardCopy[i][j] = plansza[i][j];

			if (boardCopy[i][j] == graczID || boardCopy[i][j] == 2 * graczID) ++myCnt;
			if (boardCopy[i][j] == -graczID || boardCopy[i][j] == 2 * (-graczID)) ++oponentCnt;

		}
	}

	alfabetaFirst(depthMax, -1000000, 1000000);

	if(bestMove.ID != 0) makeMove(bestMove);
}


/**
	Funkcja sprawdza czy dla danego pionka czy jest mozliwy ruch

	@param id ID gracza wykonujacego ruch w danym posunieciu.
	@return czy mozliwy ruch dla aktualnie rozpatrywanego pionka o wsp(w_,k_) w aktualnym posunieciu
*/

bool Komputer::possibleMoves(int ID)
{
	bool moves = false;


	if(biciePossible) moves = bicie(ID, w_, k_);

	else  //jesli nie ma bicia
	{
		if (czyRuchBezBicia(ID, 1, k_, w_) || czyRuchBezBicia( ID, -1, k_, w_))
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
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
		{
			k_ = j;
			w_ = i;
			if (boardCopy[i][j] == graczID)
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

	int id = graczID;

	for (int i = 0; i < pos; ++i)
	{
		k_ = nextColumn[i];  //root
		w_ = nextRow[i];  //root

		std::list<Move> nextMoves = nextPositions( id, 1, k_, w_); //w prawo
		std::list<Move> left = nextPositions( id, -1, k_, w_);
		nextMoves.splice(nextMoves.end(),left); //w lewo

		if (pos == 1 && nextMoves.size() == 1)
		{
			bestMove = nextMoves.front();
			return 0;
		}
		while (!nextMoves.empty())
		{
			makeMove(nextMoves.front());

			int result = alfabeta(depth - 1, alpha, beta, -id);
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
	numer kolumny i wiersza w kt�rych umieszczony zostal zeton w poprzednim ruchu (w celu efektywnego sprawdzenia
	czy po ruchu nie wystapil stan terminalny).


	@param depth Glebokosc przeszukiwania drzewa gry.
	@param alpha Najlepszy wynik dla gracza maksymalizujacego.
	@param beta Najlepszy wynik dla gracza minimalizujacego.
	@param id ID gracza wykonujacego ruch w danym posunieciu.


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
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
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
			std::list<Move> left = nextPositions(ID, -1, k_, w_);
			nextMoves.splice(nextMoves.end(), left); //w lewo


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
			std::list<Move> left = nextPositions(ID, -1, k_, w_);
			nextMoves.splice(nextMoves.end(), left ); //w lewo


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
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
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

	@param id ID gracza wykonujacego ruch w danym posunieciu.
	@param wiersz wiersz aktualnie rozpatrywanego pionka
	@param kol kolumna aktualnie rozpatrywanego pionka
	@return czy mozliwe bicie dla pionka o wsp(wiersz,kol) w aktualnym posunieciu
*/
bool Komputer::bicie(int ID, int wiersz, int kol)
{


	if (kol-2 >= 0 && (wiersz + ID * 2) >= 0 && (wiersz + ID * 2) < size_)
	{
		if (boardCopy[wiersz + ID * 1][kol - 1] == -(ID))
		{
			if (boardCopy[wiersz + ID * 2][kol - 2] == 0)
			{
				return true;
			}
		}
	}

	if (kol+2 < size_ && (wiersz + ID * 2) >= 0 && (wiersz + ID * 2) < size_)
	{
		if (boardCopy[wiersz + ID * 1][kol + 1] == -(ID))
		{
			if (boardCopy[wiersz + ID * 2][kol + 2] == 0)
			{
				return true;
			}

		}
	}


	//bicia do tylu
	if (kol - 2 >= 0 && (wiersz - ID * 2) >= 0 && (wiersz - ID * 2) < size_)
	{
		if (boardCopy[wiersz - ID * 1][kol - 1] == -(ID))
		{
			if (boardCopy[wiersz - ID * 2][kol - 2] == 0)
			{
				return true;
			}
		}
	}

	if (kol+2 < size_ && (wiersz - ID * 2) >= 0 && (wiersz - ID * 2) < 8)
	{
		if (boardCopy[wiersz - ID * 1][kol + 1] == -(ID))
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
	Funkcja sprawdza przymus bicia w danym posunieciu.
	Dla kazdego pionka gracza wykonujacego ruch sprawdza czy jest mozliwe bicie
	jesli chociaz jeden ma mozliwe bicie to zwraca true

	@param id ID gracza wykonujacego ruch w danym posunieciu.
	@return czy jest przymus bicia w aktualnym posunieciu
*/
bool Komputer::czyBicie(int ID )
{
	biciePossible = false;


	bool pom = false;
	//sprawdzenie czy jest przymus bicia
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
		{
			if(boardCopy[i][j] == ID)	pom = bicie(ID, i, j);
			if (pom) biciePossible = true;
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

	int ocena = 0;
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
		{
			if (boardCopy[i][j] == graczID) ocena += waga_pionka;
			if (boardCopy[i][j] == -graczID) ocena += -waga_pionka;
			if (boardCopy[i][j] == 2*graczID) ocena += waga_damki;
			if (boardCopy[i][j] == -2*graczID) ocena += -waga_damki;
		}
	}

	return ocena;
}

/**
	Znajduje wszystkie mozliwe ruchy dla aktualnie rozpatrywanego pionka i zapisuje je do listy.
	Wywoluje sie rekurancyjnie w celu sprawdzenia mozliwych bic wielokrotnych.

	@param id ID gracza wykonujacego ruch w danym posunieciu.
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
		if (czyRuchBezBicia(ID, dir, k, w))  //czy nie damka
		{
			Move newMove(w , k, w + ID, k + dir, ID);
			myMoves.push_back(newMove);
		}
	}
	else {

		if (boardCopy[w][k] == ID && k + dir * 2 < size_ && k + dir * 2 >= 0 && w + ID * 2 >= 0 && w + ID * 2 < size_
			&& boardCopy[w + ID * 2][k + dir * 2] == 0 && boardCopy[w + ID * 1][k + dir * 1] == -ID)    //bicie w przod
		{

			Move newMove(w, k, w + 2 * ID, k + 2 * dir, ID, w + ID * 1, k + dir * 1);
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
				for (list<Move>::iterator it = myMoves.begin(); it != myMoves.end(); it++)
				{
					(*it).addCaptured(w + ID * 1, k + dir * 1);
				}
				for (int i = 0; i < lastsize; ++i) myMoves.pop_front();
			}
		}

		if (boardCopy[w][k] == ID && k + dir * 2 < size_ && k + dir * 2 >= 0 && w - ID * 2 >= 0 && w - ID * 2 < size_
			&& boardCopy[w - ID * 2][k + dir * 2] == 0 && boardCopy[w - ID * 1][k + dir * 1] == -ID)    //bicie w tyl
		{

			Move newMove(w, k, w - 2 * ID, k + 2 * dir, ID, w - ID * 1, k + dir * 1);
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
				for (list<Move>::iterator it = myMoves.begin(); it != myMoves.end(); it++)
				{
					(*it).addCaptured(w - ID * 1, k + dir * 1);
				}
				for (int i = 0; i < lastsize; ++i) myMoves.pop_front();
			}
		}

	}

	return myMoves;
}

/**
	Sprawdza mozliwosc najprostszego ruchu bez bicia w kierunku okreslonym przez dir.

	@param id ID gracza wykonujacego ruch w danym posunieciu.
	@param dir okresla kierunek ruchu ;1 ruch w prawo ;-1 ruch w lewo
	@param k kolumna aktualnie rozpatrywanego pionka
	@param w wiersz aktualnie rozpatrywanego pionka
	@return true jesli jest mozliwy ruch
*/
bool Komputer::czyRuchBezBicia( int ID, int dir, int k, int w)
{

	return (boardCopy[w][k] == ID && k + dir * 1 < size_ && k + dir * 1 >= 0 && boardCopy[w + ID * 1][k + dir * 1] == 0 && w + ID >= 0 && w + ID < size_);
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
	boardCopy[move.from[0]][move.from[1]] = move.ID;
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
	if (bestMove.ID != 0)
	{
		return bestMove;
	}
	return bestMove;
}
