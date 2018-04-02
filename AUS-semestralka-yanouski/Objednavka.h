#pragma once

#include "structures\heap_monitor.h"
#include <iostream>
#include "Den.h"
#include <string>

using namespace std;

enum tovar {
	hranolky,
	lupienky
};

class Objednavka {
private:
	int cena;
	string zakaznik;
	tovar typ;
	unsigned short int region;
	int mnozstvo;
	Den datumObjednavky, datumDorucenia;
public:
	Objednavka();
	Objednavka(int, string, unsigned short int, tovar, int, Den, Den);
	~Objednavka();
	//get
	int getCena()const;
	string getZakaznik()const;
	int getMnozstvo()const;
	Den getDatumObjednavky()const;
	Den getDatumDorucenia()const;
	tovar getTyp()const;
	unsigned short int getRegion()const;
	string getNazovSpolocnosti()const;
	//set
	void setCena(double);
	void setMnozstvo(int);
	void setDatumObjednavky(int, int, int);
	void setDatumDorucenia(int, int, int);
	void setTyp(tovar);
	void setZakaznik(string);
	void setRegion(unsigned short int);


	friend ostream& operator<<(ostream&, const Objednavka&);
};

inline ostream& operator<<(ostream& out, const Objednavka& obj) {
	string typ;
	switch (obj.getTyp()) {
		case hranolky:
			typ = "Hranolky"; break;
		case lupienky:
			typ = "Lupienky"; break;
	}
	return out << "Nazov: " << obj.getNazovSpolocnosti() << "\nTyp: " << typ << "\nMnozstvo: " << obj.getMnozstvo() << "\nCena: " << obj.getCena() << "\nEvidencia: " << obj.getDatumObjednavky() << "\nDatum dorucenia: " << obj.getDatumDorucenia() << "\n";
}