#pragma once

#include "structures\heap_monitor.h"
#include <iostream>
#include "structures\list\linked_list.h"
#include "Vozidlo.h"
#include "Zakaznik.h"
#include "Objednavka.h"
#include "Farma.h"
#include "Den.h"
#include <fstream>

using namespace structures;
using namespace std;

class Sklad {
private:
	LinkedList<Farma*> farmy;
	LinkedList<Vozidlo*> vozidla;
	LinkedList<Zakaznik*> zakaznici;
	double zzemiaky, oolej, oochutenie;
	int llupienky, hhranolky;
	Den aktualny;
	int aktualnyKapital;
public:
	Sklad();
	~Sklad();
	//get
	LinkedList<Farma*>& getFarmy();
	LinkedList<Vozidlo*>& getVozidla();
	LinkedList<Zakaznik*>& getZakaznici();
	double getZemiaky()const;
	double getOlej()const;
	double getOchutenie()const;
	int getLupienky()const;
	int getHranolky()const;
	Den getAktualny()const;
	int getAktualnyKapital()const;
	//set
	void setZemiaky(double);
	void setOlej(double);
	void setOchutenie(double);
	void setLupienky(int);
	void setHranolky(int);
	void setDen(int, int, int);
	void setAktualnyKapital(int);
	//add
	void addVozidlo(string, tovar);
	void addVozidlo(string, tovar, Den);
	void addFarma(string, polotovar);
	void addObjednavka(string, tovar, int, int, Den);
	void addZakaznik(string, unsigned short int);
	//vypisy
	void vypisAktualnyDen();
	void vypisFarmy();
	void vypisVozidla();
	void vypisObjednavky();
	void vypisZakaznikov();
	//funkcionalita
	void dalsiDen();
	void kontrolaNa7Dni();
	void objednajZemiaky(double);
	void objednajOlej(double);
	void objednajOchutenie(double);
	void kontrolaDalsiDen();
	void uloz();
	void nacitaj();
	void menu();
};