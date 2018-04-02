#pragma once

#include "structures\heap_monitor.h"
#include "structures\stack\implicit_stack.h"
#include "Objednavka.h"
#include <string>

using namespace structures;
using namespace std;

class Vozidlo {
private:
	double nosnost;
	tovar typ;
	ImplicitStack<Objednavka*> naklad;
	string SPZ;
	Den zaradenie;
	int spotreba, nasobok;
public:
	Vozidlo();
	Vozidlo(string, tovar, Den);
	~Vozidlo();
	//get
	tovar getTyp()const;
	double getNosnost()const;
	string getSPZ()const;
	Den getZaradenie()const;
	int getSpotreba()const;
	int getNasobok()const;
	//set
	void setSPZ(string);
	void setNosnost(double);
	void setTyp(tovar);
	void setZaradenie(int, int, int);
	void setSpotreba(int);
	void setNasobok(int);

	void naloz(Objednavka*);
	Objednavka* vyloz();
	Objednavka* peekDalsiaObjednavka();
	void pridajSpotrebu(int);

	friend ostream& operator<<(ostream&, const Vozidlo&);
};

inline ostream& operator<<(ostream& out, const Vozidlo& vozidlo) {
	switch (vozidlo.getTyp()){
		case hranolky:
			return out << "SPZ: " << vozidlo.getSPZ() << "\nNosnost: " << vozidlo.getNosnost() << "\nTyp: " << "Hranolky\nEvidencia: " << vozidlo.getZaradenie() << "\nSpotreba: " << vozidlo.getSpotreba() << "\n";
		case lupienky:
			return out << "SPZ: " << vozidlo.getSPZ() << "\nNosnost: " << vozidlo.getNosnost() << "\nTyp: " << "Lupienky\nEvidencia: " << vozidlo.getZaradenie() << "\nSpotreba: " << vozidlo.getSpotreba() << "\n";
	}
}