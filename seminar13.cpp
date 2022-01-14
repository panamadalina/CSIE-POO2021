#include<iostream>
#include<list>
using namespace std;

/*polimorfism*/
/*
1.override -> late biding -> executie

2. overloading -> early binding -> compilarii

*/

//int suma(int a, int b) {
//	return a + b;
//}

//double suma(double a, double b) {
//	return a + b;
//}

//fctie template
template<class TIP>
TIP suma(TIP a, TIP b) {
	return a + b;//spr op+
}
//a=MAX_INT
//b=MAX_INT


/*-----------------------------------*/

enum TipParfum {
	BARBAT = 1,
	FEMEIE = 2,
	COPIL = 3
};
class IComerciabilOnline {
	virtual float getPretFinal() = 0;
};
class Parfum :IComerciabilOnline {

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

/*------------------------------------------------------*/
template<class T>
class Colectie {
	T *elemente;
	int nrElem;

public:
	Colectie() {
		this->nrElem=0;
		this->elemente = NULL;
	}
	Colectie(int nrElem, T* elem ) {
		this->nrElem = nrElem;
		this->elemente = new T[nrElem];
		for (int i = 0; i < nrElem; i++) {
			this->elemente[i] = elem[i];
		}
	}
	//constr copiere
	Colectie(const Colectie& c) {
		this->nrElem = c.nrElem;
		if (c.elemente != NULL) {
			this->elemente = new T[c.nrElem];
			for (int i = 0; i < c.nrElem; i++) {
				this->elemente[i] = c.elemente[i];
			}
		}
		else {
			this->elemente = NULL;
		}
	}
	~Colectie() {
		if (this->elemente != NULL) {
			delete[] this->elemente;
		}
	}
	//<<
	//friend ostream& operator<< <T>(ostream& out, const Colectie<T>& c);

	friend ostream& operator<<(ostream& out, const Colectie& c) {
		out << "\nColectia are nrelem:  " << c.nrElem << ": ";
		for (int i = 0; i < c.nrElem; i++) {
			out << c.elemente[i] << " ";
		}
		return out;
	}
	//
	void sortare();
};

//template<class T>
//ostream& operator<< (ostream& out, const Colectie<T>& c) {
	/*out << "\nCOlectia are nrelem:  " << c.nrElem << ": ";
	for (int i = 0; i < c.nrElem; i++) {
		out << c.elemente[i] << " ";
	}
	return out;*/
//
//}
template<class T>
void Colectie<T>::sortare() {
	for (int i = 0; i <nrElem-1 ; i++) {
		for (int j = i +1 ; j < nrElem; j++) {
			if (elemente[i] > elemente[j]) {
				T aux = elemente[i];
				elemente[i] = elemente[j];
				elemente[j] = aux;
			}
		}
	}
}

template<class T=float, int n=2>
class Lista {
	T elem[n];
	int nrElem;
	//etc

};


//parfum - 
//derivam -> parfum->parfumDif
template<class T>
class ParfumDif :public Parfum {
	T x;
};

template<class T>
class ColectieDif :public Colectie<T> {
	T x;
};


class ClasaNormala : public ParfumDif<int>{//!
	//nu mai avem T
};
int main() {

	cout << suma(2, 3);
	cout << endl << suma(2.5, 3.5);
	//char* a = new char[10];
	//char* b = new char[20];

	//cout << suma(a, b);

	int* vectNote = new int[3];
	vectNote[0] = 10;
	vectNote[1] = 8;
	vectNote[2] = 9;


	Colectie<int> colectieNote(3,vectNote);
	cout << colectieNote;


	Parfum p1("Dior", 200, true, TipParfum::BARBAT);
	Parfum p2("Chanel", 150, true, TipParfum::FEMEIE);
	Parfum* vectParfum = new Parfum[2];//constr fara param Parfum
	vectParfum[0] = p1;// op= parfum
	vectParfum[1] = p2;//op = parfum

	Colectie<Parfum>colectieParfum(2, vectParfum);
	cout << endl << endl << colectieParfum;
	colectieParfum.sortare();
	cout << endl << "\nDupa sortare:";
	cout << colectieParfum;

	Lista<int, 3>list1;
	Lista<int>list2;
	Lista<>list3;

	//include<string>
	//include<math.h>
	//include<list> -> STL standard template library
	list<Parfum>listaSTL1(2);
	listaSTL1.push_back(p1);
	return 0;
}