#pragma once

#include "structures\heap_monitor.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "structures\list\linked_list.h"

using namespace std;
using namespace structures;

enum polotovar {
	zemiaky,
	olej,
	ochutenie
};

class Farma {
private:
	string nazov;
	int cena;
	double cenaPriemer;
	LinkedList<int> ceny;
	polotovar typ;
	double mnozstvo;
public:
	Farma();
	Farma(string, polotovar);
	~Farma();
	//get
	string getNazov()const;
	int getCena()const;
	polotovar getTyp()const;
	double getPriemer()const;
	int getMnozstvo()const;
	LinkedList<int>& getCeny();
	//set
	void setMnozstvo(int);
	void setNazov(string);
	void setTyp(polotovar);
	void setCena(int);
	void setCenaPriemer(double);
	//funkcionalita
	void genMnozstvo();
	void urobPriemer();
	void genCena();
	void addCeny(int);



	friend ostream& operator<<(ostream&, const Farma&);
};

inline ostream& operator<<(ostream& out, const Farma& farma) {
	string typ_polotovaru;
	switch (farma.getTyp()){
		case zemiaky: typ_polotovaru = "Zemiaky"; break;
		case olej: typ_polotovaru = "Olej"; break;
		case ochutenie: typ_polotovaru = "Ochutovadlo"; break;
	}
	return out << "Nazov: " << farma.getNazov() << "\nTyp: " << typ_polotovaru << "\nCena: " << farma.getCena() << "\nPriemerna Cena: " << farma.getPriemer() << "\n";
}