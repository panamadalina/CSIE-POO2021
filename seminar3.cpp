#include<iostream>
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

//enumeratie - tip de data ce rastrange numarul de valori posibile
//la cele de mai jos
enum ziSaptamana { luni = 1, marti = 2, miercuri = 3,joi=4,vineri=5};


struct Student {
	char* nume;//4B
	int varsta;//4B
	bool lucreaza;//1B
};

//constructor
Student initializareStudent(const char* nume, int varsta, bool lucreaza) {
	Student student;
	student.varsta = varsta;
	student.nume = new char[strlen(nume) + 1];
	strcpy(student.nume, nume);
	student.lucreaza = lucreaza;

	return student;
}

void afisareStudent(Student s) {
	printf("\n Studentul: %s - varsta:%d", s.nume, s.varsta);
	if (s.lucreaza) {
		cout << "- lucreaza";
	}
	else {
		cout << "- nu lucreaza";
	}
}

void schimbaVarsta(Student* s, int varstaNoua) {
	(*s).varsta = varstaNoua;
}

void incepeJob(Student& s) {
	s.lucreaza = true;
}
void main() {
	/*Exemplu 1:*/

	//cout << ziSaptamana::luni;
	ziSaptamana zi = ziSaptamana::vineri;

	cout << "\nzi:" << zi;
	zi = (ziSaptamana)1;

	/*------------------------------------------------------------*/
	/*Exemplu 2*/

	//Operatiile aritmetice permise asupra pointerilor sunt:
	//adunarea / scaderea unei constante, 
	//incrementarea / decrementarea si 
	//scaderea a doi pointeri de acelasi tip.

	int x = 10;
	int* pointer = &x;
	//A) creste adresa salvata in pointer cu sizeof(int)
	cout << "\nAdresa pointer1=" << pointer << endl;
	pointer++;
	cout << "\nAdresa pointer2=" << pointer << endl;

	//B) q salveaza o adresa mai mica cu 2 * sizeof(int) decat pointer
	int* qpointer = pointer - 2;
	cout << "\nAdresa pointer3=" << qpointer << endl;

	//C) Adunare 2 pointeri -> INTERZIS
	//cout << pointer + qpointer;//Nu merge!!
	
	//D) diferenta a doi pointeri este un intreg
	//si reprezinta cate variabile de tip int, in acest caz particular
	//incap intre cele doua adrese de memorie
	printf("%dScadere dintre 2 pointeri=\n", pointer - qpointer);

	/*---------------------------------------------------------*/
	/*Exemplu 3:*/

	//Adunarea cu 1, face ca un pointer sa indice urmatorul obiect de acelasi tip iar
	//decrementarea face ca el sa indice obiectul imediat anterior in spatiul de memorie.

	
	int* v = new int[3];
	v[0] = 0; v[1] = 1; v[2] = 2;
	cout << "\nv=" << v;
	cout <<"\n*v+1 = "<< * v + 1;//NU e bine! e o coincidenta!


	v[0] = 1; v[1] = 3; v[2] = 5;
	//cout << *(v + 1);
	cout <<"\n*(1+v) = "<< * (1 + v);
	//cout << endl << "\n*(v+1)=v[1]";
	
	delete[]v;
	/*-------------------------------------------------------------*/
	
	/*Exemplu 4: Struct*/

	Student student = initializareStudent("Madalina", 24, true);
	afisareStudent(student);
	//memory leak
	//pointer la structura:
	Student* pstudent = &student;
	schimbaVarsta(&student, 30);
	afisareStudent(student);

	schimbaVarsta(pstudent, 100);//shallow copy
	afisareStudent(student);

	/*-----------*/
	//pointer la structura:
	Student* ps2 = new Student();
	ps2->varsta = 19;
	ps2->nume = new char[strlen("Lucian") + 1];
	strcpy(ps2->nume, "Lucian");
	ps2->lucreaza = false;
	afisareStudent(*ps2);
	//memory leak

	//	//o matrice
	//	//o adresa la adresa la un element
	//	//adresa unui vector de elemente
	//	//vector de adrese;

	Student** pms = (Student**)malloc(2*sizeof(Student*));
	for (int i = 0; i < 2; i++) {
		pms[i] = (Student*)malloc(sizeof(Student));
		//pms[i] = new Student();//nu merge
	}
	pms[0]->varsta = 20;
	pms[0]->nume = new char[strlen("Ana") + 1];
	strcpy(pms[0]->nume, "Ana");
	pms[0]->lucreaza = true;

	afisareStudent(*pms[0]);
	delete[] pms[0]->nume;
	
	for (int i = 0; i < 2; i++) {
		free(pms[i]);
	}
	free(pms);

	delete[]ps2->nume;
	delete ps2;


	delete[] student.nume;

	cout << endl << endl;
	//matrice alocata dinamic cu 2 linii si 3 coloane
	int nrLinii = 2;
	int nrColoane = 3;
	int** matrice = new int* [nrLinii];
	for (int i = 0; i < nrLinii; i++)
	{
		matrice[i] = new int[nrColoane];
	}
	int k = 0;
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane; j++)
		{
			matrice[i][j] = ++k;//preincrementare
		}
	}
	cout << endl;
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane; j++)
		{
			cout << matrice[i][j] << " ";
		}
		cout << endl;
	}

	//dezalocare matrice alocata dinamic
	for (int i = 0; i < nrLinii; i++)
	{
		delete[] matrice[i];
	}
	delete[] matrice;


	_CrtDumpMemoryLeaks();
}