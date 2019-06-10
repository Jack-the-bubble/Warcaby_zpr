#ifndef _GRA_H_
#define _GRA_H_
#include "Plansza.h"
#include "Gracz.h"
#include "Klient.h"
#include "Komputer.h"
#include "Move.h"
#include <iostream>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Komputer> Kom;
typedef boost::shared_ptr<Klient> Kl;
typedef boost::python::list pyList;
/**
 *  \brief     Glowna klasa gry, jej metoda play jest petla glowna gry, kontroluje przeplyw ruchow i sprawdza terminalnosc planszy
 *  \author    Katarzyna Seweryn
 *  \date      2019
 */
class Gra
{
public:
	Gra();
	~Gra();
	void drukuj(); 			/**wypisanie planszy na konsole*/
	void play(); 			/**symulacja gry pc vs pc*/
	void klientMoveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap); /**aktualizacja ruchu klienta*/
	void computerUpdate(); 	/**aktualizacja ruchu komputera*/
	void player1notify(); 	/**aktualizacja planszy po ruchu klienta - testowanie*/
	void changePlansza();	/**aktualizacja gry po ruchu klienta z serwera*/
	void player2notify();	/**aktualizacja planszy por ruchu komputera*/
	void assignID(int i);	/**przypisanie ID*/
	void reset();
	int getID();
	int klientGet();
	void klientSet(int i);
	pyList convertAndSend();/**wyslanie ruchu komputera do serwera*/

	Plansza plansza;  		/**< plansza gry   */
	Kl player1;				/**gracz 1 - klient*/
	Kom player2;			/**gracz2 - komputer*/
	int ID_;
	const int KOLUMNY = 8; /**< rozmiar planszy */
};

#endif