#include "Zakaznik.h"


Zakaznik::Zakaznik() {
	this->nazov_spolocnosti = "dummy";
	this->region = 0;
}
Zakaznik::Zakaznik(string nazov, unsigned short int region) {
	this->nazov_spolocnosti = nazov;
	this->region = region;
}
Zakaznik::~Zakaznik() {
	for (Objednavka* temp : this->obj) {
		delete temp;
		temp = nullptr;
	}
	this->obj.clear();
}
//get
string Zakaznik::getNazovSpolocnosti()const {
	return this->nazov_spolocnosti;
}
unsigned short int Zakaznik::getRegion()const {
	return this->region;
}
ArrayList<Objednavka*>& Zakaznik::getObjednavky() {
	return this->obj;
}
//set
void Zakaznik::setNazovSpolocnosti(string nazov) {
	this->nazov_spolocnosti = nazov;
}
void Zakaznik::setRegion(unsigned short int region) {
	this->region = region;
}
void Zakaznik::pridajObjednavku(Objednavka* obj) {
	this->obj.add(obj);
}
Objednavka* Zakaznik::odoberObjednavku(tovar typ, Den datumDorucenia) {
	for (int i = 0; i < this->obj.size(); i++) {
		if (this->obj[i]->getTyp() == typ && this->obj[i]->getDatumDorucenia() == datumDorucenia) {
			return this->obj.removeAt(i);
		}
	}
	return nullptr;
}