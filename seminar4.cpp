#include<iostream>
#include<stdio.h>
#include <crtdbg.h>
#include<string>
using namespace std;

//clasa = user defined datatype
//Membrii unei clase: atribute & metode 

struct Pers {
	int varsta;
};

class Persoana {

	//atribut fara specif tip de accesare:
	int varsta;
	//metode:
public:
	int idPersoana;
	void metoda1() {
		cout << "\nMetoda1";
	}
	void metoda2();
protected:
	bool lucreaza;
};

void Persoana::metoda2() {
	cout << "\nMetoda2";
}
//protected:
class Angajat :Persoana {
	//Persoana p;
	Angajat() {
		this->idPersoana = 0;
		this->lucreaza = true;
	}
};

class Student {


private:
	//atribute
	int varsta;
	char nume[10];

	//membrii publici
public:
	int idStudent;


	//Exemplu 3:constructor implicit (fara parametri)
	Student()
	{
		strcpy(this->nume, "Anonim");
		this->idStudent = 1234;
		this->varsta = 18;

		cout << "\n Apelare constructor implicit(fara parametrii)" << endl;
	}

	//Exemplu 4: constructor cu parametrii
	Student(int id, int varsta) {
		this->idStudent = id;
		this->varsta = varsta;
		cout << "\n Apelare constructor cu 2 param" << endl;
	}

	Student(const char nume[], int id, int varsta) {
		strcpy(this->nume, nume);
		this->idStudent = id;
		this->varsta = varsta;
		cout << "\n Apelare constructor cu 3 param" << endl;
	}

	//Exemplu 5: getteri
	int getVarsta() {
		return this->varsta;
	}

	//Exercitiu 1: Faceti get si ptr nume
	char* getNume() {
		return this->nume;
	}

	//Exemplu 6: setteri:
	void setVarsta(int v) {
		if (v > 0) {
			this->varsta = v;
			//sa nu faceti prostia:
			//this->getVarsta() = v;

		}
		else {
			throw "varsta incorecta";
		}
	}


	/*Alte metode:
	- constructor de copiere
	- supraincarcare =
	- supaincarcare operatori + - ++ --
	- alte functii:
	*/
	int calcVarstaPesteZeceAni() {
		return this->varsta + 10;
	}
};

int main() {
	//Ce este o clasa?
	// 	   Ce contine o clasa?

	//EXEMPLU 1: Tiuri de accesari
	Persoana p; //acesta e un obiect <-> o instanta a unei clase
//	Pers pers;
	//de ce nu pot accesa varsta din clasa la fel cum o fac din struct?
	// 3 tipuri de accesari:

	/*public - members are accessible from outside the class
	private (BY DEFaULT) - members cannot be accessed (or viewed) from outside the class --->> INCAPSULARE!
	protected - members cannot be accessed from outside the class, however, they can be accessed in inherited classes. You will learn more about Inheritance later.*/


	p.idPersoana = 1234;
	cout << p.idPersoana;


	/*EXEMPLU 2: Tipuri de metode -> din clasa, din afara clasei*/

	p.metoda1();
	p.metoda2();

	/*EXEMPLU 3: constructor implicit */
	Student s;
	cout << "\ns.idStud:" << s.idStudent;
	//s este un obiect
	//unde e salvat acest obiect?
	//stack

	/*EXEMPLU 4: constructor cu mai multi parametrii*/
	/*ordinea trebuie sa fie aceeasi*/
	Student s2(2, 20);


	//Student* ps = new Student(3,30);
	////ps este un pointer la un obiect de tip Student
	////acest obiect este alocat dinamic pentru ca avem NEW
	//cout << "\nps.idStud(constructor cu param):" << ps->idStudent;
	//delete ps;

	Student* ps2 = new Student("Mada", 4, 40);
	cout << "\nps2.idStud:" << ps2->idStudent;

	cout << "\n\nGETTERI:";
	/*EXEMPLU 5: getteri si setteri ptr public/private/protected*/
	//Ce facem? doar afisam din main atributele care st publice?
	// folosim getteri & setteri

	int varstaMada = ps2->getVarsta();
	cout << "\nps2.getVarsta():" << varstaMada;

	char* numeMada = ps2->getNume();
	cout << "\nps2.getNume():" << numeMada;

	//setteri:
	cout << "\n\nSETTERI:";
	ps2->setVarsta(20);
	cout << "\nps2.getVarsta():" << varstaMada;//se modifica de la setter
	//i se intoarce doar o valoare
	varstaMada = ps2->getVarsta();
	cout << "\nDupa setter:ps2.getVarsta():" << varstaMada;

	//ps2->setVartsa(30);
	varstaMada = 30;
	cout << "\nps2.varsta2:" << ps2->getVarsta(); //ramane neschimbat
	//nu retine spatiul unde este alocat
	try {
		ps2->setVarsta(-10);

	}
	catch (const char* excep) {
		cout << "\nCodul arunca o exceptie:" << excep;
	}

	//1:
	char* nume = ps2->getNume();
	cout << "\nps2.nume:" << nume;
	//2:
	strcpy(nume, "Madalina");
	cout << "\nnume2:" << nume<<"--> S-a modificat variabila din main";
	char* nume2 = ps2->getNume();
	cout << "\nps2.nume2:" << nume2<<"--> S-a modificat atributul din clasa";//se modifica

	int varsta = ps2->getVarsta();


	delete ps2;

	_CrtDumpMemoryLeaks();
	return 0;
}