#include<iostream>
#include<crtdbg.h>
using namespace std;

class Student {
private:
	char* nume;
	int varsta;

public:

	/*Exemplu 1: cls Student + constructor fara param*/
	Student() {
		cout << "+Apelare constructor fara param";
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->varsta = 0;
	}

	/*constr cu params - Var1: */
	/*Student(const char nume[],int varsta) {
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->varsta = varsta;
	}*/
	//Var2:
	Student(const char nume[], int varsta = 18) :varsta(varsta) {
		cout << "\n+Apelare constructor cu param pentru: " << nume;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		//this->varsta = varsta;
	}
	void afisare() {
		if (this->nume != NULL) {
			cout << "\nAfisare stud: Nume: " << this->nume;
		}
		cout << " - varsta: " << this->varsta;
	}

	//Exemplu 2: Destructor:
	~Student() {
		cout << "\n+Apelare destructor: " << this->nume;
		delete[] this->nume;
	}

	//Exemplu 3: constr copiere: foloseste ca parametrii pointerul 'this' si referinta(&) la obiectul care trebuie copiat
	Student(const Student& s) {//primeste referinta de tip student "&" -> ma duc la adresa obiectului pe care vreau sa il copiez

		//delete[] this->nume; //Nu se folos la constr copiere! -> obiectul in care se face clona este un obiect neinitializat, nu avem ce sa dezalocam
		cout << "\n+Apelare Constructor de copiere pentru - " << s.nume;
		if (s.nume != NULL)
		{
			this->nume = new char[strlen(s.nume) + 1];
			strcpy(this->nume, s.nume);
		}
		else
			this->nume = NULL;
		this->varsta = s.varsta;
	}

	//Exemplu 4: supraincarcare op =
	Student& operator=(const Student& s)
	{
		cout << "\n+Apelare operator= pentru - " << s.nume;
		if (this->nume != NULL)
			delete[] this->nume;//dezalocam ptr ca op = se apeleaza ptr obiecte deja create
		if (s.nume != NULL)//facem alocarea si copierea
		{
			this->nume = new char[strlen(s.nume) + 1];
			strcpy(this->nume, s.nume);

		}
		else
			this->nume = NULL;
		this->varsta = s.varsta;
		return *this;
	}


	//Exemplu6:
	int getVarsta() {
		return this->varsta;
	}

};

//Exemplu 6:

Student studBatran(Student vs[], int nrStud) {
	Student batran;
	if (nrStud > 0) {
		batran = vs[0];
	}
	else {
		return NULL;
	}
	for (int i = 0; i < nrStud; i++) {
		if (vs[i].getVarsta() > batran.getVarsta()) {
			batran = vs[i];
		}
	}

	return batran;

}
int main() {
	/*
	-Recap: ce este o clasa?
	-Ce contine o clasa?
	-Cate tipuri de accesari avem?
	-Ce este un constructor?
	-Cate tipuri de constructori am facut?
	*/

	/*Exemplu 1: cls Student + constructor fara param*/
	Student s1;
	cout << "\n--> S1:";
	s1.afisare();

	/*
	POINTERUL THIS:
		- Utilizat, în special în metode, pentru a accesa obiectul curent (cel prelucrat de
			acea metodă)
		- El salvează adresa acestui obiect
		- Este necesară utilizarea acestuia atunci când metoda are un parametru cu
			aceeași denumire ca un atribut al clasei deoarece variabilele locale (în acest caz
			parametrul) au prioritate în fața variabilelor globale (în acest caz atributul) cu
			aceeași denumire
	*/

	/*Avem 2 tipuri de apelari ptr acelasi constructor cu parametrii:*/
	Student s2("Mada");
	Student s3("Ana", 20);

	cout << "\n--> S2:";
	s2.afisare();

	cout << "\n--> S3:";
	s3.afisare();

	/*-----------------------------------------------------------------------------------------------------*/
	/*Exemplu2: Destructor*/
	_CrtDumpMemoryLeaks();
	/*AVEM MEMORY LEAK!

	desi s1,s2,s3 nu st pointeri, fiecare contine alocat un pointer de char
	Folosim DESTRUCTOR:
		Utilizat la distrugerea obiectelor (dezalocarea memoriei alocate în constructor)
		Dacă nu există destructor într-o anumită clasă, atunci automat se crează unul gol
	*/

	/*implementam destructorul -> stergem memoria alocata in heap -> tot *apare* ca avem memory leak*/
	/*de ce? ptr ca destructorul se apeleaza cand se termina programul de executat! */
	/*inaintea destructorului se executa  _CrtDumpMemoryLeaks();  ---> care este doar o metoda de generare a rapoartelor Memory Leak
	deci nu mai merge sa folosim CRT! */
	/*-----------------------------------------------------------------------------------------------------*/


		/*Exemplu3: Constructor de copiere:

		- Constructor utilizat explicit pentru a crea copii ale obiectelor
		- Compilatorul apelează totuși implicit constructorul de copiere în două situații:
			--> transmiterea unui obiect ca parametru într-o funcție prin valoare
			--> returnarea unui obiect prin valoare dintr-o funcție
		- Dacă nu este creat explicit, atunci se crează automat un constructor de copiere
			în clasă ce realizează copiere byte cu byte a obiectului curent
		- Acest lucru poate crea probleme atunci când clasa are membri pointeri

		*/
	Student s4(s3);//Apel explicit constr de copiere
	Student s5 = s4;//Apel explicit constr de copiere	

	//daca nu explicitam constructorul de copiere  --> avem eroare --> ptr ca acest constructor de copiere implicit doar copiaza bit cu bit
	//nu stie sa aloce ptr char* nume o noua zona de memorie

	cout << "\n--> S4:";
	s4.afisare();

	cout << "\n--> S5:";
	s5.afisare();

	/*-----------------------------------------------------------------------------------------------------*/

	/*Exemplu 4: Supraincarcarea op = */
	//daca nu supraincarcam operatorul =  --> avem eroare --> ptr ca acest operator(=) scris implicit de calculator doar copiaza bit cu bit
	//nu stie sa aloce ptr atributul obiectul nou (char* nume) o noua zona de memorie
	s5 = s1;
	cout << "\n--> S5 dubla 2:";
	s5.afisare();


	/* Operatorul =
	- Apelat automat atunci când se copiază informații dintr-un obiect existent într-un
		alt obiect existent (spre deosebire de constructorul de copiere ce copiază
		informații dintr-un obiect existent într-un obiect nou)
	- Poate returna void (situație în care nu este permis apelul în cascadă) sau adresa
		obiectului tocmai creat (ce permite apelul în cascadă)
	- La fel ca și constructorul de copiere primește drept parametru obiectul din care
		se face copierea

	*/

	/*Exemplu 6:*/
	cout << "\n\nCreare objs:";
	Student st1("St1", 21);

	Student st2("St2", 22);
	Student st3("St3", 28);
	Student vs[]{ st1, st2, st3 };

	Student vstud[] = { st1,st2,st3 };
	Student strCautat = studBatran(vstud, 3);
	cout << "\n\nCel mai batran student:";
	strCautat.afisare();

	cout << "\n\nEND!";

	/*
	REGULA!
	Orice clasa care are membrii pointeri, treb sa contina:
	- constructori
	- destructor
	- constructor de copiere
	- supraincarcarea op =
	*/

	return 0;
}