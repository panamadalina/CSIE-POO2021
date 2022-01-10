#include<iostream>
using namespace std;
enum TipParfum {
	BARBAT=1,
	FEMEIE=2,
	COPIL=3
};
class IComerciabilOnline {
	virtual float getPretFinal() = 0;
};
class Parfum:IComerciabilOnline {

	char* brand;
	float pret;
	bool esteImpachetat;
	static float costImpachetare;
	TipParfum tip;
public:
	Parfum() {
		this->brand = new char[strlen("necunoscut") + 1];
		strcpy(this->brand, "necunoscut");
		this->pret = 0;
		this->esteImpachetat = false;
		this->tip = TipParfum::FEMEIE;
	}
	Parfum(const char* brand, float pret, bool esteImpachetat, TipParfum tip) {
		if (brand == NULL || strlen(brand) <= 2) {
			throw "\nnume brand invalid!\n";
		}
		this->brand = new char[strlen(brand) + 1];
		strcpy(this->brand, brand);
		this->pret = pret;
		this->esteImpachetat = esteImpachetat;
		this->tip = tip;

	}
	float getPretFinal() {
		if (this->esteImpachetat) {
			return this->pret + this->costImpachetare;
		}
		else {
			return this->pret;
		}
	}
	~Parfum() {
		if (this->brand) {
			delete[] this->brand;
		}
	}
	Parfum(const Parfum& p) {
		this->brand = new char[strlen(p.brand) + 1];
		strcpy(this->brand, p.brand);
		this->pret = p.pret;
		this->esteImpachetat = p.esteImpachetat;
		this->tip = p.tip;
	}
	Parfum& operator=(const Parfum& p) {
		if (this->brand) {
			delete[] this->brand;
		}
		this->brand = new char[strlen(p.brand) + 1];
		strcpy(this->brand, p.brand);
		this->pret = p.pret;
		this->esteImpachetat = p.esteImpachetat;
		this->tip = p.tip;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Parfum p);

	bool operator>(Parfum& p) {
		if (this->getPretFinal() > p.getPretFinal()) {
			return true;
		}
		else return false;
	}
};

float Parfum::costImpachetare = 50;
//void creeazaOBJ() {
//	Parfum p1("Y", 200, true, TipParfum::FEMEIE);
//}

ostream& operator<<(ostream& out, Parfum p) {
	out << "\nParfumul" << p.brand << " are pret-raft: " << p.pret << " este pentru: ";
	if (p.tip == TipParfum::FEMEIE) {
		out << " femeie";
	}
	if (p.tip == TipParfum::BARBAT) {
		out << " barbat";
	}
	if (p.tip == TipParfum::COPIL) {
		out << " copil";
	}
	if (p.esteImpachetat) {
		out << "-> este impachetat";
	}
	else {
		out << "-> NU este impachetat";
	}
	return out;
}
class ISortable {
	virtual void sort()=0;
};
class IAfisare {
	virtual void afisare() = 0;
};
class Colectie:public ISortable,public IAfisare {
	Parfum* listaParfumuri;
	int nrParfumuri;
public:
	Colectie(int nrParfumuri, Parfum* listaParfumuri) {
		this->nrParfumuri = nrParfumuri;
		this->listaParfumuri = new Parfum[nrParfumuri];
		for (int i = 0; i < nrParfumuri; i++) {
			this->listaParfumuri[i] = listaParfumuri[i];
		}
	}
	void sort() {
		for (int i = 0; i < this->nrParfumuri-1; i++) {
			for (int j = i; j < this->nrParfumuri; j++) {
				if (this->listaParfumuri[i] > this->listaParfumuri[j]) {//this->listaParfumuri[i].operator>(  this->listaParfumuri[j]  )
					Parfum aux = this->listaParfumuri[i];
					this->listaParfumuri[i] = this->listaParfumuri[j];
					this->listaParfumuri[j] = aux;
				}
			}
		}
	}
	void afisare() {
		for (int i = 0; i < this->nrParfumuri; i++) {
			cout << this->listaParfumuri[i];
		}
	}
};

int main() {
	
	try {

		Parfum p1("Dior", 200, true, TipParfum::FEMEIE);
		cout << p1;//cout.operator<<(Parfum p);
		cout << "\n pret final:" << p1.getPretFinal();

		Parfum p2("Chanel", 300, false, TipParfum::BARBAT);
		Parfum p3("Zara", 100, true, TipParfum::COPIL);

		Parfum* listaParfumuri = new Parfum[3];
		listaParfumuri[0] = p1;
		listaParfumuri[1] = p2; 
		listaParfumuri[2] = p3;


		Colectie collection(3,listaParfumuri);
		cout << endl;
		collection.afisare();
		collection.sort();
		cout << endl << endl << "dupa sort:" << endl;
		collection.afisare();


	}
	catch (const char* excp) {
		cout << excp;
	}
	return 0;
}
