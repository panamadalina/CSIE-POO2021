#include<iostream>
#include<vector>
using namespace std;

class Piesa
{
private:
	char* denumire;
	float valoare;

public:
	Piesa()
	{
		this->denumire = new char[strlen("N/A") + 1];
		strcpy(this->denumire, "N/A");
		this->valoare = 0;
	}

	Piesa(const char* denumire, float valoare)
	{
		if (denumire != NULL)
		{
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else
			this->denumire = NULL;
		this->valoare = valoare;
	}

	Piesa(const Piesa& p)
	{
		if (p.denumire != NULL)
		{
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
		}
		else
			this->denumire = NULL;
		this->valoare = p.valoare;
	}

	Piesa& operator=(const Piesa& p)
	{
		if (this->denumire != NULL)
			delete[] this->denumire;
		if (p.denumire != NULL)
		{
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
		}
		else
			this->denumire = NULL;
		this->valoare = p.valoare;
		return *this;
	}

	~Piesa()
	{
		if (this->denumire != NULL)
			delete[] this->denumire;
	}

	friend ostream& operator<<(ostream& out, const Piesa& p)
	{
		out << "\nPiesa " << p.denumire << " are valoarea: " << p.valoare;
		return out;
	}
	void setDenumire(const char* den) {

		if (den !=  NULL) {
			if (this->denumire != NULL) {
				delete[] this->denumire;
			}
			this->denumire = new char[strlen(den) + 1];
			strcpy(this->denumire, den);
		}

	}
	void setValoare(float val) {
		if (val > 0) {
			this->valoare = val;
		}
		else {
			throw "valoare invalida";
		}
	}

	friend class Aparat;

	float GetValoare() {
		return this->valoare;
	}
	/*virtual void faCeva() = 0;*/
};

class Aparat
{
private:
	const int id;
	int durataFunctionare;
	Piesa* colectiePiese;
	int nrPiese;

public:
	//constructor fara param
	Aparat() : id(0)
	{
		durataFunctionare = 0;
		colectiePiese = nullptr;
		nrPiese = 0;
	}

	//constructor cu toti param
	Aparat(int id, int durataFunctionare, Piesa* vectorPiese, int nrPiese) : id(id) {
		this->durataFunctionare = durataFunctionare;
		this->colectiePiese = new Piesa[nrPiese];
		for (int i = 0; i < nrPiese; i++) {
			this->colectiePiese[i] = vectorPiese[i];
		}
		this->nrPiese = nrPiese;
	}
	//constructor copiere

	Aparat(const Aparat& aparat) :id(aparat.id) {
		this->durataFunctionare = aparat.durataFunctionare;
		this->colectiePiese = new Piesa[aparat.nrPiese];
		for (int i = 0; i < aparat.nrPiese; i++) {
			this->colectiePiese[i] = aparat.colectiePiese[i];
		}
		this->nrPiese = aparat.nrPiese;
	}

	//operator =

	Aparat& operator=(const Aparat& aparat) {
		if (this->colectiePiese != NULL) {
			delete[] this->colectiePiese;
			this->colectiePiese = nullptr;
		}
		this->durataFunctionare = aparat.durataFunctionare;
		this->colectiePiese = new Piesa[aparat.nrPiese];
		for (int i = 0; i < aparat.nrPiese; i++) {
			this->colectiePiese[i] = aparat.colectiePiese[i];
		}
		this->nrPiese = aparat.nrPiese;
	}

	//operator <<
	friend ostream& operator<<(ostream& out, const Aparat& aparat) {
		out << aparat.id << "\n" << aparat.nrPiese << "\n" << aparat.durataFunctionare;
		for (int i = 0; i < aparat.nrPiese; i++) {
			out << aparat.colectiePiese[i] << " ";
		}
		return out;
	}

	//destructor
	~Aparat() {
		if (this->colectiePiese != NULL) {
			delete[] this->colectiePiese;
			this->colectiePiese = nullptr;
		}
	}

	//op+=
	Aparat operator+=(Piesa p) {
		Piesa* copy = NULL;
		if (this->colectiePiese != NULL) {
			copy = new Piesa[this->nrPiese];
			for (int i = 0; i < this->nrPiese; i++) {
				copy[i] = this->colectiePiese[i];
			}
			delete[] this->colectiePiese;
		}

		this->colectiePiese = new Piesa[this->nrPiese + 1];
	
		for (int i = 0; i < this->nrPiese; i++) {
			this->colectiePiese[i] = copy[i];
		}
		this->colectiePiese[this->nrPiese] = p;//op = din Piesa
		this->nrPiese++;
		return *this;
	}

	operator float() {
		float suma = 0;
		for (int i = 0; i < this->nrPiese; i++) {
			//suma += this->colectiePiese[i].getValoare();
			suma += this->colectiePiese[i].valoare;
		}
		return suma;
	}

	//Piesa operator[](int index) {

	//}

	Piesa& operator[](int index)
	{
		if (index >= 0 && index < nrPiese)
			return colectiePiese[index];
		else
			throw exception("Index invalid");
	}

};


class PiesaSchimb : public Piesa {
	int anInlocuire;
public:
	PiesaSchimb()
	{
		anInlocuire = 0;
	}
	PiesaSchimb(const char* denumire, float valoare, int anInlocuire) : Piesa(denumire, valoare)
	{
		this->anInlocuire = anInlocuire;
	}

	

};


void main()
{
	Piesa p1;
	Piesa p2("Piesa2", 20.4f);
	Piesa p3 = p2;
	p3.setDenumire("Piesa3");
	try {
		p3.setValoare(35.5f); //de adaugat validari
	}
	catch (const char* exp) {
		cout << exp;
	}
	
	cout << p3;

	Piesa piese[3] = { p1,p2,p3 };
	Aparat mf1(12, 5, piese, 3);//cod,durata, piese,nrPiese

	Piesa p4("Piesa4", 12.0f);
	mf1 += p4;//mf1.operator+=(p4)
	cout << endl<<endl<<"\nAfisare aparat\n"<<mf1;
	cout << "\nValoarea totala a pieselor unui aparat este: " << (float)mf1 << endl;

	//Mesajul afisat la generarea exceptiei este: ?Index out of range!?
	try {
		cout << mf1[6];
		mf1[0] = p4;
		cout << mf1[0];
	}
	catch (exception ex) {
		cout << ex.what() << endl;
	}
	mf1[0] = p4;
	cout << "\nAfisare dupa try-catch\n"<<mf1;
	//Sa se construiasca clasa PiesaSchimb, derivata public din clasa Piesa, 
	//care contine atributul an inlocuire (int).

	PiesaSchimb ps1("PiesaS1", 10.0f, 2013);
	PiesaSchimb ps2("PiesaS2", 50.0f, 2013);
	Piesa* pp = &ps1;
	cout << "\nValoarea unei piese de schimb este: " << pp->GetValoare() << endl;
	pp = &p2;
	cout << "\nValoarea unei piese este: " << pp->GetValoare() << endl;

	vector<Aparat*> mijloaceFixe;
	//Sa se declare folosind o colectie de elemente de tip pointer la Aparat 
	//utilizand clasa STL vector. 
	//Sa se adauge elementele mf1 si mf2 in colectie si, utilizand un iterator, sa se 
	//parcurga colectia cu afisarea la consola a fiecarui obiect.

	Aparat mf2(12, 5, piese, 2);

	Aparat* pmf1 = &mf1;
	Aparat* pmf2 = &mf2;
	mijloaceFixe.push_back(&mf1);
	mijloaceFixe.push_back(pmf2);
	cout << "\nSTL:\n";
	vector<Aparat*>::iterator it;//int i=0;i<size()
	for (it = mijloaceFixe.begin(); it != mijloaceFixe.end(); it++) {
		cout << "\n" << *(*it);
	}


}