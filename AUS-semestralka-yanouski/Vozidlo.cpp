#include "Vozidlo.h"


Vozidlo::Vozidlo() {
	this->SPZ = "ABX_DUMMY";
	this->nosnost = 2;
	this->typ = lupienky;
}
Vozidlo::Vozidlo(string spz, tovar typ, Den zaradene) {
	this->SPZ = spz;
	this->typ = typ;
	this->spotreba = 0;
	this->zaradenie = zaradene;
	if (this->typ == hranolky) {
		this->nosnost = 5000;
		this->nasobok = 100;
	}else{
		this->nosnost = 2000;
		this->nasobok = 70;
	}
}
Vozidlo::~Vozidlo() {
	while (this->naklad.size() != 0) {
		delete this->naklad.pop();
	}
	this->naklad.clear();
}
tovar Vozidlo::getTyp()const {
	return this->typ;
}
double Vozidlo::getNosnost()const {
	return this->nosnost;
}
void Vozidlo::setSPZ(string spz) {
	this->SPZ = spz;
}
string Vozidlo::getSPZ()const {
	return this->SPZ;
}
void Vozidlo::naloz(Objednavka* obj) {
	this->naklad.push(obj);
}
Objednavka* Vozidlo::vyloz() {
	return this->naklad.pop();
}
Objednavka* Vozidlo::peekDalsiaObjednavka() {
	return this->naklad.peek();
}
void Vozidlo::pridajSpotrebu(int region) {
	this->spotreba += (region * this->nasobok);
}
Den Vozidlo::getZaradenie()const {
	return this->zaradenie;
}
int Vozidlo::getSpotreba()const {
	return this->spotreba;
}
int Vozidlo::getNasobok()const {
	return this->nasobok;
}
void Vozidlo::setNosnost(double nosnost) {
	this->nosnost = nosnost;
}
void Vozidlo::setTyp(tovar typ) {
	this->typ = typ;
}
void Vozidlo::setZaradenie(int den, int mesiac, int rok) {
	this->zaradenie = Den(den, mesiac, rok);
}
void Vozidlo::setSpotreba(int spotreba) {
	this->spotreba = spotreba;
}
void Vozidlo::setNasobok(int nasobok) {
	this->nasobok = nasobok;
}