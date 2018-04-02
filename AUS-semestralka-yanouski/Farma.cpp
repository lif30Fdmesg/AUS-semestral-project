#include "Farma.h"


Farma::Farma() {
	this->nazov = "dummy";
	this->cena = 100;
	this->typ = zemiaky;
}
Farma::Farma(string nazov, polotovar typ) {
	this->nazov = nazov;
	this->typ = typ;
	for (int temp : this->ceny) {
		temp = 0;
	}
	genCena();
	genMnozstvo();
}
Farma::~Farma() {
	this->ceny.clear();
}
//get
string Farma::getNazov()const {
	return this->nazov;
}
int Farma::getCena()const {
	return this->cena;
}
polotovar Farma::getTyp()const {
	return this->typ;
}
double Farma::getPriemer()const {
	return this->cenaPriemer;
}
int Farma::getMnozstvo()const {
	return this->mnozstvo;
}
//set
void Farma::setMnozstvo(int mnozstvo) {
	this->mnozstvo = mnozstvo;
}
void Farma::setNazov(string nazov) {
	this->nazov = nazov;
}
void Farma::genCena() {
	srand(time(NULL));
	switch (this->typ) {
	case zemiaky:
		this->cena = rand() % 3 + 1;
		break;
	case olej:
		this->cena = rand() % 4 + 1;
		break;
	case ochutenie:
		this->cena = rand() % 2 + 1;
	}
	if (this->ceny.size() < 30) {
		this->ceny.add(this->cena);
		urobPriemer();
	}else{
		this->ceny.removeAt(0);
		this->ceny.add(cena);
		urobPriemer();
	}
}
void Farma::setCenaPriemer(double priemer) {
	this->cenaPriemer = priemer;
}
void Farma::genMnozstvo() {
	srand(time(NULL));
	switch (this->typ) {
	case zemiaky:
		this->mnozstvo = rand() % 5000;
		break;
	case olej:
		this->mnozstvo = rand() % 1000;
		break;
	case ochutenie:
		this->mnozstvo = rand() % 5000;
	}
}
//funkcionalita
void Farma::urobPriemer() {
	this->cenaPriemer = 0;
	for (double temp : this->ceny) {
		this->cenaPriemer += temp;
	}
	this->cenaPriemer /= this->ceny.size();
}
void Farma::setTyp(polotovar typ) {
	this->typ = typ;
}
void Farma::setCena(int cena) {
	this->cena = cena;
}
LinkedList<int>& Farma::getCeny() {
	return this->ceny;
}
void Farma::addCeny(int cena) {
	this->ceny.add(cena);
}