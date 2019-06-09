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
	void drukuj();
	void play();
	void klientMoveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap);
	void computerUpdate();
	void player1notify();
	void changePlansza();
	void player2notify();
	void assignID(int i);
	void reset();
	int getID();
	int klientGet();
	void klientSet(int i);
	pyList convertAndSend();

	Plansza plansza;  /**< plansza gry   */
	Kl player1;
	Kom player2;
	int ID_;
//	Gracz* player1;  /**< wskaznik na gracza 1 */
//	Gracz* player2;  /**< wskaznik na gracza 2 */
	const int KOLUMNY = 8; /**< rozmiar planszy */
};

#endif