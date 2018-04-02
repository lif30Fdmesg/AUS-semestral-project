#include "Den.h"

Den::Den() { //konstruktor
	this->den = 1;
	this->mesiac = 1;
	this->rok = 1979;
}

Den::Den(const Den& other) { //kopirovaci konstruktor
	this->den = other.getDen();
	this->mesiac = other.getMesiac();
	this->rok = other.getRok();
}

Den::Den(int den, int mesiac, int rok) { // konkretny konstruktor
	this->den = den;
	this->mesiac = mesiac;
	this->rok = rok;
}

Den::~Den() { // destruktor

}

int Den::getDen() const { //getter
	return this->den;
}

int Den::getMesiac() const { //getter
	return this->mesiac;
}

int Den::getRok() const { //getter
	return this->rok;
}

void Den::setDen(int den) { //setter
	this->den = den;
}

void Den::setMesiac(int mesiac) {//setter
	this->mesiac = mesiac;
}
//setter
void Den::setRok(int rok) {
	this->rok = rok;
}

void Den::next() { //nacita dalsi den
	if (this->mesiac == 1 ||
		this->mesiac == 3 ||
		this->mesiac == 5 ||
		this->mesiac == 7 ||
		this->mesiac == 8 ||
		this->mesiac == 10 ||
		this->mesiac == 12) {
		if (this->den == 31) {
			this->mesiac += 1;
			this->den = 1;
			if (this->mesiac == 13) {
				this->mesiac = 1;
				this->rok += 1;
			}
		}
		else this->den += 1;
	}
	else {
		if (this->mesiac == 2) {
			//myslim, ze toto je podmienka prestupneho roku
			if (this->rok % 4 == 0) {
				if (this->den == 29) {
					this->mesiac = 3;
					this->den = 1;
				}
				else {
					this->den += 1;
				}
			}else{
				if (this->den == 28) {
					this->mesiac = 3;
					this->den = 1;
				}
				else {
					this->den += 1;
				}
			}
			//sice som nasiel nieco ohladom delitelnosti 100 a 400, ale to tu nejdem implementovat
		}
		else {
			if (this->den == 30) {
				this->mesiac += 1;
				this->den = 1;
			}
			else {
				this->den += 1;
			}
		}
	}
}


void Den::operator=(const Den& other) { //operator priradenia
	this->den = other.getDen();
	this->mesiac = other.getMesiac();
	this->rok = other.getRok();
}

