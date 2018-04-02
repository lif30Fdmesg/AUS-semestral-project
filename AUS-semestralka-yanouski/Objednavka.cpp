#include "Objednavka.h"


Objednavka::Objednavka():
	zakaznik("dummy"), 
	cena(0), 
	typ(hranolky), 
	mnozstvo(0) {}

Objednavka::Objednavka(int cena, string zak, unsigned short int region, tovar typ, int mnozstvo, Den datObjed, Den datDoruc):
	cena(cena),
	zakaznik(zak),
	region(region),
	typ(typ),
	mnozstvo(mnozstvo),
	datumObjednavky(datObjed),
	datumDorucenia(datDoruc) {}

Objednavka::~Objednavka() {

}
//get
int Objednavka::getCena()const {
	return this->cena;
}
string Objednavka::getZakaznik()const {
	return this->zakaznik;
}
int Objednavka::getMnozstvo()const {
	return this->mnozstvo;
}
Den Objednavka::getDatumObjednavky()const {
	return this->datumObjednavky;
}
Den Objednavka::getDatumDorucenia()const {
	return this->datumDorucenia;
}
tovar Objednavka::getTyp()const {
	return this->typ;
}
unsigned short int Objednavka::getRegion()const {
	return this->region;
}
string Objednavka::getNazovSpolocnosti()const {
	return this->zakaznik;
}
//set
void Objednavka::setCena(double cena) {
	this->cena = cena;
}
void Objednavka::setMnozstvo(int mnozstvo) {
	this->mnozstvo = mnozstvo;
}
void Objednavka::setDatumObjednavky(int den, int mesiac, int rok) {
	this->datumObjednavky = Den(den, mesiac, rok);
}
void Objednavka::setDatumDorucenia(int den, int mesiac, int rok) {
	this->datumDorucenia.setDen(den);
	this->datumDorucenia.setMesiac(mesiac);
	this->datumDorucenia.setRok(rok);
}
void Objednavka::setTyp(tovar typ) {
	this->typ = typ;
}
void Objednavka::setZakaznik(string nazov) {
	this->zakaznik = nazov;
}
void Objednavka::setRegion(unsigned short int region) {
	this->region = region;
}