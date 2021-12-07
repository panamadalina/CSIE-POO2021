#include<iostream>
using namespace std;

class Persoana {

private:
	char* nume;
	int varsta;
public:
	//int varsta;
	//constructor fara parametrii
	Persoana()
	{
		cout << "\n~Apel constructor fara param->Persoana: Anonim";
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->varsta = 0;
	}
	//constructor cu parametrii
	Persoana(const char* nume, int varsta) : varsta(varsta)
	{
		cout << "\n~Apel constructor cu param->Persoana: " << nume;
		if (nume != NULL)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		else
			this->nume = NULL;
	}

	//constructor de copiere
	Persoana(const Persoana& p)
	{
		cout << "\n~Apel constructor de copiere->Persoana: " << p.nume;
		if (p.nume != NULL)
		{
			this->nume = new char[strlen(p.nume) + 1];
			strcpy(this->nume, p.nume);
		}
		else
			this->nume = NULL;
		this->varsta = p.varsta;

	}

	//Operatorul egal

	Persoana& operator=(const Persoana& p)
	{
		cout << "\n~Apel operator = ->Persoana: " << p.nume;
		if (this->nume != NULL)
		{
			this->nume = new char[strlen(p.nume) + 1];
			strcpy(this->nume, p.nume);
		}
		else
			this->nume = NULL;
		this->varsta = p.varsta;
		return *this;
	}

	//destructori

	~Persoana()
	{
		cout << "\n~Apel destructor->Persoana: " << this->nume;
		if (this->nume != NULL)
			delete[]this->nume;
	}

	char* getNume()
	{
		return this->nume;
	}

	int getVarsta()
	{
		return this->varsta;
	}
	friend ostream& operator<<(ostream& out, Persoana p);
};

ostream& operator<<(ostream& out, Persoana p)
{
	out << "\n";
	out << "-->Persoana: " << p.nume << " are " << p.varsta << " ani ";
	return out;
}

class Student :public Persoana {
private:
	char* facultate;
	
public:
	Student() {
		cout << "\n~Apel constructor fara param->Student: Necunoscut";
		this->facultate = new char[strlen("necunoscut") + 1];
		strcpy(this->facultate, "Necunoscut");
		//this->varsta = 0;
	}
	~Student() {
		cout << "\n~Apel destructor->Student: " << this->facultate;
		if (this->facultate != NULL) {
			delete[]this->facultate;
		}
	}
	Student(const char*n,int v, const char*f):Persoana(n,v){
	//	Persoana::Persoana(n, v);
		cout << "\n~Apel constructor cu params->Student: "<<n;
		this->facultate = new char[strlen(f) + 1];
		strcpy(this->facultate, f);
		
	}

	//constructor de copiere
	Student(const Student& s):Persoana(s)
	{
		cout << "\n~Apel constructor de copiere->Student: ";
		this->facultate = new char[strlen(s.facultate) + 1];
		strcpy(this->facultate, s.facultate);
	}
	//op=
	Student& operator=(const Student& s) {
		cout << "\n~Apel operator = ->Student: " << s.facultate;
		Persoana::operator=(s);
		if (this->facultate != NULL) {
			delete[] this->facultate;
		}
		this->facultate = new char[strlen(s.facultate) + 1];
		strcpy(this->facultate, s.facultate);
		return *this;
	}
	friend ostream& operator<<(ostream& out, Student s);
};

ostream& operator<<(ostream& out, Student s)
{
	out << "\n";
	out << "Studentul " << s.getNume() << " are " << s.getVarsta() << " este la facult: " << s.facultate;
	return out;
}


class Angajat :public Persoana {


};

class Domeniu {
	Student* listaStudenti;
	int nrStudenti;
	char* denumire;
public:
	Domeniu() {
		this->denumire = new char[strlen("necunoscut") + 1];
		strcpy(this->denumire, "Necunoscut");
		this->listaStudenti = NULL;
		this->nrStudenti = 0;
	}

	Domeniu(const char* denumire, Student* listaS, int nrS) {

		cout << "\n~Apel constructor cu params->Domeniu: " << denumire;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this -> listaStudenti = new Student[nrS];
		this->nrStudenti = nrS;
		for (int i = 0; i < nrS; i++) {
			this->listaStudenti[i] = listaS[i];
		}

	}
	friend ostream& operator<<(ostream& out, Domeniu d);
};

ostream& operator<<(ostream& out, Domeniu d) {
	out << "\nIn domeniul: "<<d.denumire << "avem studentii: ";
	for (int i = 0; i < d.nrStudenti; i++) {
		out << d.listaStudenti[i]<<" ";
	}
	return out;
}
int main() {

	//Persoana p;

	//Student s;
	//s.varsta = 0;
	//Persoana p1;
	Student s1("Mada",21,"CSIE");
	//Persoana p1("Alex", 22);
	/*Regula*/
	//cout << p1;
	//p1 = s1;//merge->se pierde info ->upcasting
//	s1 = p1;//nu merge-> putem supr op=
	//cout << p1;
	//Student s2 = s1;

	//op=
	Student s2;
	s2 = s1;
	cout << s1;
	Persoana p1 = s1;
	cout << p1;
	cout << endl << endl;
	Student s3("Alex", 22, "Poli");
	Student s4("Andrei", 24, "Univ-info");
	Student* listaStud = new Student[3];
	listaStud[0] = s1;
	listaStud[1] = s3;
	listaStud[2] = s4;
	cout << endl << endl;
	Domeniu d("IT", listaStud, 3);
	cout << d;
	cout << endl << endl;
	return 0;
}