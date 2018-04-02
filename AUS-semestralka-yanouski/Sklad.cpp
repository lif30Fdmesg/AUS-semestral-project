#include "Sklad.h"

Sklad::Sklad() :
	aktualny(1, 4, 2018),
	aktualnyKapital(0),
	zzemiaky(0),
	llupienky(0),
	hhranolky(0),
	oolej(0),
	oochutenie(0)
	{}
Sklad::~Sklad() {
	
	for (Farma* temp : this->farmy) {
		delete temp;
		temp = nullptr;
	}
	for (Vozidlo* temp : this->vozidla) {
		delete temp;
		temp = nullptr;
	}
	for (Zakaznik* temp : this->zakaznici) {
		delete temp;
		temp = nullptr;
	}
	this->farmy.clear();
	this->vozidla.clear();
	this->zakaznici.clear();

}
//get
LinkedList<Farma*>& Sklad::getFarmy() {
	return this->farmy;
}
LinkedList<Vozidlo*>& Sklad::getVozidla() {
	return this->vozidla;
}
LinkedList<Zakaznik*>& Sklad::getZakaznici() {
	return this->zakaznici;
}
//add
void Sklad::addVozidlo(string spz, tovar typ) {
	this->vozidla.add(new Vozidlo(spz, typ, this->aktualny));
}
void Sklad::addVozidlo(string spz, tovar typ, Den den) {
	this->vozidla.add(new Vozidlo(spz, typ, den));
}
void Sklad::addFarma(string nazov, polotovar typ) {
	this->farmy.add(new Farma(nazov, typ));
}
//void Sklad::addObjednavka(Zakaznik* zak, Objednavka* obj) {
//	for (Zakaznik* temp : this->zakaznici) {
//		if (temp->getNazovSpolocnosti() == zak->getNazovSpolocnosti() &&
//			temp->getRegion() == zak->getRegion()) {
//			temp->pridajObjednavku(obj);
//			return;
//		}
//	}
//	this->zakaznici.add(zak);
//	addObjednavka(zak, obj);
//}
void Sklad::addObjednavka(string nazov, tovar typ, int mnozstvo, int cena, Den dorucenie) {
	if (dorucenie - this->aktualny < 7) {
		cout << "\nObjednavka nepridana! Menej ako 7 dni do dorucenia!\n";
		return;
	}
	for (Zakaznik* temp : this->zakaznici) {
		if (temp->getNazovSpolocnosti() == nazov) {
			temp->pridajObjednavku(new Objednavka(cena, nazov, temp->getRegion(), typ, mnozstvo, this->aktualny, dorucenie));
			return;
		}
	}
	unsigned short int region;
	cout << "\nZakaznik neexistuje - musite zadat region kam zakaznik patri: ";
	cin >> region;
	this->zakaznici.add(new Zakaznik(nazov, region));
	addObjednavka(nazov, typ, mnozstvo, cena, dorucenie);
}
void Sklad::addZakaznik(string nazov, unsigned short int region) {
	this->zakaznici.add(new Zakaznik(nazov, region));
}
//vypisy
void Sklad::vypisFarmy() {
	char l, u;
	l = 'a';
	u = 'A';
	for (int i = 0; i < 26; i++) {
		for (Farma* temp : this->farmy) {
			if (temp->getNazov()[0] == l || temp->getNazov()[0] == u) {
				cout << "++++++++++++++++++++++++++++++\n";
				cout << *temp;
				cout << "++++++++++++++++++++++++++++++\n";
			}
		}
		l++;
		u++;
	}
}
void Sklad::vypisVozidla() {
	Den den(1, 4, 2018);
	unsigned short int check = 0;
	while (check != this->vozidla.size()) {
		for (Vozidlo* temp : this->vozidla) {
			if (temp->getZaradenie() == den) {
				cout << "++++++++++++++++++++++++++++++\n";
				cout << *temp;
				cout << "++++++++++++++++++++++++++++++\n";
				check++;
			}
		}
		den.next();
	}
}
void Sklad::vypisObjednavky() {
	for (Zakaznik* temp : this->zakaznici) {
		for (Objednavka* temp2 : temp->getObjednavky()) {
			cout << "++++++++++++++++++++++++++++++\n";
			cout << *temp2;
			cout << "++++++++++++++++++++++++++++++\n";
		}
	}
}
void Sklad::vypisZakaznikov() {
	for (Zakaznik* temp : this->zakaznici) {
		cout << "++++++++++++++++++++++++++++++\n";
		cout << *temp;
		cout << "++++++++++++++++++++++++++++++\n";
	}
}
void Sklad::vypisAktualnyDen() {
	cout << this->aktualny;
}
void Sklad::dalsiDen() {
	for (Farma* temp : this->farmy) {
		temp->genCena();
		temp->genMnozstvo();
	}
	this->aktualny.next();
}
void Sklad::kontrolaNa7Dni() {
	//zistime kolko lupienok a hranoliek mame vyrobit za 7 dni
	double zemiaky = 0, olej = 0, ochutenie = 0;
	int lupienky = 0, hranolky = 0;
	for (Zakaznik* temp : this->zakaznici) {
		for (Objednavka* temp2 : temp->getObjednavky()) {

			if (0 > this->aktualny - temp2->getDatumDorucenia() > -8) {
				if (temp2->getTyp() == hranolky) {
					hranolky = temp2->getMnozstvo();
				}
				else {
					lupienky = temp2->getMnozstvo();
				}
			}

		}
	}
	//ideme zistit co nam chyba na 
	//1.5z+0.2o=1h
	//2z+0.4o+0.02ochut=l
	zemiaky += hranolky * 1, 5;
	zemiaky += lupienky * 2;
	olej += hranolky * 0, 2;
	olej += lupienky * 0, 4;
	ochutenie += lupienky * 0, 02;

	if (this->zzemiaky - zemiaky < 0) {
		objednajZemiaky(zemiaky - this->zzemiaky);
	}
	if (this->oolej - olej < 0) {
		objednajOlej(olej - this->oolej);
	}
	if (this->oochutenie - ochutenie < 0) {
		objednajOchutenie(ochutenie - this->oochutenie);
	}
}
void Sklad::objednajZemiaky(double mnozstvo) {
	Farma* result;
	double priemer = 9999;
	for (Farma* temp : this->farmy) {
		if (temp->getTyp() == zemiaky && temp->getPriemer() < priemer
			&& temp->getMnozstvo() != 0) result = temp;
	}
	if (mnozstvo > result->getMnozstvo()) {
		mnozstvo -= result->getMnozstvo();
		this->aktualnyKapital -= result->getCena()*result->getMnozstvo();
		this->zzemiaky += result->getMnozstvo();
		result->setMnozstvo(0);
		objednajZemiaky(mnozstvo);
	}
	else {
		this->aktualnyKapital -= result->getCena()*mnozstvo;
		this->zzemiaky += mnozstvo;
	}
}
void Sklad::objednajOlej(double mnozstvo) {
	Farma* result;
	double priemer = 9999;
	for (Farma* temp : this->farmy) {
		if (temp->getTyp() == olej && temp->getPriemer() < priemer
			&& temp->getMnozstvo() != 0) result = temp;
	}
	if (mnozstvo > result->getMnozstvo()) {
		mnozstvo -= result->getMnozstvo();
		this->aktualnyKapital -= result->getCena()*result->getMnozstvo();
		this->oolej += result->getMnozstvo();
		result->setMnozstvo(0);
		objednajOlej(mnozstvo);
	}
	else {
		this->aktualnyKapital -= result->getCena()*mnozstvo;
		this->oolej += mnozstvo;
	}
}
void Sklad::objednajOchutenie(double mnozstvo) {
	Farma* result;
	double priemer = 9999;
	for (Farma* temp : this->farmy) {
		if (temp->getTyp() == ochutenie && temp->getPriemer() < priemer
			&& temp->getMnozstvo() != 0) result = temp;
	}
	if (mnozstvo > result->getMnozstvo()) {
		mnozstvo -= result->getMnozstvo();
		this->aktualnyKapital -= result->getCena()*result->getMnozstvo();
		this->oochutenie += result->getMnozstvo();
		result->setMnozstvo(0);
		objednajOchutenie(mnozstvo);
	}
	else {
		this->aktualnyKapital -= result->getCena()*mnozstvo;
		this->oochutenie += mnozstvo;
	}
}
void Sklad::kontrolaDalsiDen() {
	double zemiaky = this->zzemiaky, olej = this->oolej, ochutenie = this->oochutenie;
	for (Zakaznik* temp : this->zakaznici) {
		for (Objednavka* temp2 : temp->getObjednavky()) {

			if (0 > this->aktualny - temp2->getDatumDorucenia() > -2) {
				cout << "++++++++++++++++++++++++++++++\n";
				cout << *temp;
				cout << *temp2;
				if (temp2->getTyp() == hranolky) {
					zemiaky -= temp2->getMnozstvo() * 1, 5;
					olej -= temp2->getMnozstvo() * 0, 2;
				}
				else {
					zemiaky -= temp2->getMnozstvo() * 2;
					olej -= temp2->getMnozstvo() * 0, 4;
					ochutenie -= temp2->getMnozstvo() * 0, 02;
				}
				if (zemiaky < 0 || olej < 0 || ochutenie < 0) {
					cout << "<---OBJEDNAVKU NIE JE MOZNE REALIZOVAT!--->" << endl;
				}
				cout << "++++++++++++++++++++++++++++++\n";
			}

		}
	}
}
double Sklad::getZemiaky()const {
	return this->zzemiaky;
}
double Sklad::getOlej()const {
	return this->oolej;
}
double Sklad::getOchutenie()const {
	return this->oochutenie;
}
int Sklad::getLupienky()const {
	return this->llupienky;
}
int Sklad::getHranolky()const {
	return this->hhranolky;
}
Den Sklad::getAktualny()const {
	return this->aktualny;
}
int Sklad::getAktualnyKapital()const {
	return this->aktualnyKapital;
}
void Sklad::setZemiaky(double zemiaky) {
	this->zzemiaky = zemiaky;
}
void Sklad::setOlej(double olej) {
	this->oolej = olej;
}
void Sklad::setOchutenie(double ochutenie) {
	this->oochutenie = ochutenie;
}
void Sklad::setLupienky(int lupienky) {
	this->llupienky = lupienky;
}
void Sklad::setHranolky(int hranolky) {
	this->hhranolky = hranolky;
}
void Sklad::setDen(int den, int mesiac, int rok) {
	this->aktualny = Den(den, mesiac, rok);
}
void Sklad::setAktualnyKapital(int aktualnyKapital) {
	this->aktualnyKapital = aktualnyKapital;
}
void Sklad::uloz() {
	ofstream out;
	out.open("sklad.sf");

	out << this->farmy.size() << endl;
	for (Farma* temp : this->farmy) {
		out << temp->getCeny().size() << endl;
		for (int temp2 : temp->getCeny()) {
			out << temp2 << endl;
		}
		out << temp->getCena() << endl;
		out << temp->getMnozstvo() << endl;
		out << temp->getNazov() << endl;
		out << temp->getPriemer() << endl;
		if (temp->getTyp() == zemiaky) {
			out << "zemiaky" << endl;
		}else if(temp->getTyp() == olej){
			out << "olej" << endl;
		}else{
			out << "ochutenie" << endl;
		}
	}
	/*
	Neukladam naklad v aute, pretoze aj kebyze to mam naprogramovane, ukladat by sa dalo iba na konci dna, kedy je auto prazdne	
	*/
	out << this->vozidla.size() << endl;
	for (Vozidlo* temp : this->vozidla) {
		out << temp->getNasobok() << endl;
		out << temp->getNosnost() << endl;
		out << temp->getSpotreba() << endl;
		out << temp->getSPZ() << endl;
		if (temp->getTyp() == hranolky) {
			out << "hranolky" << endl;
		}
		else {
			out << "lupienky" << endl;
		}
		out << temp->getZaradenie().getDen() << endl;
		out << temp->getZaradenie().getMesiac() << endl;
		out << temp->getZaradenie().getRok() << endl;
	}
	out << this->zakaznici.size() << endl;
	for (Zakaznik* temp : this->zakaznici) {
		out << temp->getObjednavky().size() << endl;
		for (Objednavka* temp2 : temp->getObjednavky()) {
			out << temp2->getCena() << endl;
			out << temp2->getDatumDorucenia().getDen() << endl;
			out << temp2->getDatumDorucenia().getMesiac() << endl;
			out << temp2->getDatumDorucenia().getRok() << endl;
			out << temp2->getDatumObjednavky().getDen() << endl;
			out << temp2->getDatumObjednavky().getMesiac() << endl;
			out << temp2->getDatumObjednavky().getRok() << endl;
			out << temp2->getMnozstvo() << endl;
			out << temp2->getNazovSpolocnosti() << endl;
			out << temp2->getRegion() << endl;
			if (temp2->getTyp() == hranolky) {
				out << "hranolky" << endl;
			}
			else {
				out << "lupienky" << endl;
			}
		}
		out << temp->getNazovSpolocnosti() << endl;
		out << temp->getRegion() << endl;
	}
	out << this->getZemiaky() << endl;
	out << this->getOlej() << endl;
	out << this->getOchutenie() << endl;
	out << this->getLupienky() << endl;
	out << this->getHranolky() << endl;
	out << this->getAktualny().getDen() << endl;
	out << this->getAktualny().getMesiac() << endl;
	out << this->getAktualny().getRok() << endl;
	out << this->getAktualnyKapital() << endl;
	out.close();
}
void Sklad::nacitaj() {
	ifstream in;
	in.open("sklad.sf");
	int size = 0, size2 = 0, tmp = 0;;
	ArrayList<int> fCeny;
	//farmy
	string fNazov;
	int fCena;
	double fPriemer;
	string fTyp;
	double fMnozstvo;

	in >> size;
	for (int i = 0; i < size; i++) {
		in >> size2;
		for (int j = 0; j < size2; j++) {
			in >> tmp;
			fCeny.add(tmp);
		}
		in >> fCena;
		in >> fMnozstvo;
		in >> fNazov;
		in >> fPriemer;
		in >> fTyp;
		if (fTyp == "zemiaky") {
			this->farmy.add(new Farma(fNazov, zemiaky));
			this->farmy[i]->setCena(fCena);
			this->farmy[i]->setCenaPriemer(fPriemer);
			this->farmy[i]->setMnozstvo(fMnozstvo);
			for (int j = 0; j < size2; j++) {
				this->farmy[i]->getCeny().add(fCeny[j]);
			}
		}
		else if (fTyp == "olej") {
			this->farmy.add(new Farma(fNazov, olej));
			this->farmy[i]->setCena(fCena);
			this->farmy[i]->setCenaPriemer(fPriemer);
			this->farmy[i]->setMnozstvo(fMnozstvo);
			for (int j = 0; j < size2; j++) {
				this->farmy[i]->getCeny().add(fCeny[j]);
			}
		}
		else {
			this->farmy.add(new Farma(fNazov, ochutenie));
			this->farmy[i]->setCena(fCena);
			this->farmy[i]->setCenaPriemer(fPriemer);
			this->farmy[i]->setMnozstvo(fMnozstvo);
			for (int j = 0; j < size2; j++) {
				this->farmy[i]->getCeny().add(fCeny[j]);
			}

		}
		fCeny.clear();
	}

	double vNozsnost;
	string vSPZ, vTyp;
	int vDen, vMesiac, vRok, vSpotreba, vNasobok;

	in >> size;
	for (int i = 0; i < size; i++) {
		in >> vNasobok;
		in >> vNozsnost;
		in >> vSpotreba;
		in >> vSPZ;
		in >> vTyp;
		in >> vDen;
		in >> vMesiac;
		in >> vRok;
		if (vTyp == "hranolky") {
			this->vozidla.add(new Vozidlo(vSPZ, hranolky, Den(vDen, vMesiac, vRok)));
		}else{
			this->vozidla.add(new Vozidlo(vSPZ, lupienky, Den(vDen, vMesiac, vRok)));
		}
		this->vozidla[i]->setNasobok(vNasobok);
		this->vozidla[i]->setNosnost(vNozsnost);
		this->vozidla[i]->setSpotreba(vSpotreba);
	}

	int oCena, oMnozstvo, ooden, oomesiac, oorok, odden, odmesiac, odrok;
	string oZakaznik, oTyp;
	unsigned short int oRegion;
	ArrayList<Objednavka*> oObjednavky;
	string zNazov;
	unsigned short int zRegion;



	in >> size;
	for (int i = 0; i < size; i++) {
		in >> size2;
		for (int j = 0; j < size2; j++) {
			in >> oCena;
			in >> odden;
			in >> odmesiac;
			in >> odrok;
			in >> ooden;
			in >> oomesiac;
			in >> oorok;
			in >> oMnozstvo;
			in >> oZakaznik;
			in >> oRegion;
			in >> oTyp;
			if (oTyp == "hranolky") {
				oObjednavky.add(new Objednavka(oCena, oZakaznik, oRegion, hranolky, oMnozstvo, Den(ooden, oomesiac, oorok), Den(odden, odmesiac, odrok)));
			}else{
				oObjednavky.add(new Objednavka(oCena, oZakaznik, oRegion, lupienky, oMnozstvo, Den(ooden, oomesiac, oorok), Den(odden, odmesiac, odrok)));
			}
		}
		in >> zNazov;
		in >> zRegion;
		this->zakaznici.add(new Zakaznik(zNazov, zRegion));
		for (int j = 0; j < size2; j++) {
			this->zakaznici[i]->getObjednavky().add(oObjednavky[j]);
			this->zakaznici[i]->getObjednavky()[j]->setCena(oCena);
			this->zakaznici[i]->getObjednavky()[j]->setDatumDorucenia(odden, odmesiac, odrok);
			this->zakaznici[i]->getObjednavky()[j]->setDatumObjednavky(ooden, oomesiac, oorok);
		}
		oObjednavky.clear();
	}

	int sden, smesiac, srok;

	in >> this->zzemiaky;
	in >> this->oolej;
	in >> this->oochutenie;
	in >> this->llupienky;
	in >> this->hhranolky;
	in >> sden;
	in >> smesiac;
	in >> srok;
	this->aktualny.setDen(sden);
	this->aktualny.setMesiac(smesiac);
	this->aktualny.setRok(srok);
	in >> this->aktualnyKapital;
	in.close();
}
void Sklad::menu() {
	char ch = ' ';
	string a, b, c, d, e, f;
	int g, h, i, j, k, l;
	while (ch != 'x') {
		cout << "aktualny den: " << this->aktualny << endl;
		cout << "1. vytvor farmara" << endl;
		cout << "2. vytvor vozidlo" << endl;
		cout << "3. vytvor zakaznika" << endl;
		cout << "4. vytvor objednavku" << endl;
		cout << "5. vypis farmarov" << endl;
		cout << "6. vypis vozidla" << endl;
		cout << "7. vypis zakaznikov" << endl;
		cout << "8. vypis objednavky" << endl;
		cout << "9. nakup \"na 7 dni\"" << endl;
		cout << "q. kontrola \"na dalsi den\"" << endl;
		cout << "w. uloz" << endl;
		cout << "e. nacitaj" << endl;
		cout << "r. dalsi den" << endl;
		cout << "x. ukonci program" << endl;
		cin >> ch;
		switch (ch) {
		case '1':
			cout << "zadajte nazov: ";
			cin >> a;
			cout << "zadajte polotovar(zemiaky, olej, ochutenie): ";
			cin >> b;
			if (b == "zemiaky") {
				this->addFarma(a, zemiaky);
			}else if (b == "olej"){
				this->addFarma(a, olej);
			}else if(b == "ochutenie"){
				this->addFarma(a, ochutenie);
			}
			else cout << "nespravna volba";
			break;
		case '2':
			cout << "zadajte SPZ: ";
			cin >> a;
			cout << "zadajte typ tovaru(lupienky, hranolky): ";
			cin >> b;
			if (b == "lupienky") {
				this->addVozidlo(a, lupienky);
			}
			else if (b == "hranolky") {
				this->addVozidlo(a, hranolky);
			}
			else cout << "nespravna volba";
			break;
		case '3':
			cout << "zadajte nazov: ";
			cin >> a;
			cout << "zadajte typ region: ";
			cin >> g;
			if (g < 0) {
				cout << "nespravna volba";
				break;
			}
			this->addZakaznik(a, g);
			break;
		case '4':
			cout << "zadajte nazov zakaznika: ";
			cin >> a;
			cout << "zadajte typ tovaru(lupienky, hranolky): ";
			cin >> b;
			cout << "zadajte mnozstvo: ";
			cin >> h;
			cout << "zadajte cenu: ";
			cin >> i;
			cout << "den dorucenia: ";
			cin >> j;
			cout << "mesiac: ";
			cin >> k;
			cout << "rok: ";
			cin >> l;
			if (b == "lupienky") {
				this->addObjednavka(a, lupienky, h, i, Den(j, k, l));
			}
			else if (b == "hranolky") {
				this->addObjednavka(a, hranolky, h, i, Den(j, k, l));
			}
			else cout << "nespravna volba";
			break;
		case '5':
			this->vypisFarmy();
			break;
		case '6':
			this->vypisVozidla();
			break;
		case '7':
			this->vypisZakaznikov();
			break;
		case '8':
			this->vypisObjednavky();
			break;
		case '9':
			this->kontrolaNa7Dni();
			break;
		case 'q':
			this->kontrolaDalsiDen();
			break;
		case 'w':
			this->uloz();
			break;
		case 'e':
			this->nacitaj();
			break;
		case 'r':
			this->dalsiDen();
			break;
		case 'x':
			cout << "Dovidenia!";
			break;
		default:
			cout << "nespravna volba!" << endl;
		}
	}
}