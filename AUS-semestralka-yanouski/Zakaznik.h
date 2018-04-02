#pragma once

#include "Objednavka.h"
#include "structures\list\array_list.h"

using namespace std;
using namespace structures;

class Zakaznik {
private:
	string nazov_spolocnosti;
	ArrayList<Objednavka*> obj;
	unsigned short int region;
public:
	Zakaznik();
	Zakaznik(string, unsigned short int);
	~Zakaznik();
	//get
	string getNazovSpolocnosti()const;
	unsigned short int getRegion()const;
	ArrayList<Objednavka*>& getObjednavky();
	//set
	void setNazovSpolocnosti(string);
	void setRegion(unsigned short int);
	//funkcionalita
	void pridajObjednavku(Objednavka*);
	Objednavka* odoberObjednavku(tovar, Den);

	friend ostream& operator<<(ostream&, const Zakaznik&);
};

inline ostream& operator<<(ostream& out, const Zakaznik& zak) {
	return out << "Nazov: " << zak.getNazovSpolocnosti() << "\nRegion: " << zak.getRegion() << "\n";
}