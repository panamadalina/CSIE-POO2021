#include <iostream>
#include<crtdbg.h>

using namespace std;

class Student {
private:
	char* nume;
	int varsta;
	bool lucreaza;

public:
	//constr fara param
	//cu param
	//copy contr
	//op =
	//destr
	
	static int nrStudenti;//-> la nivelul intregii clase
	//varsta difera de la un obj la alt obj
	Student() {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->varsta = 0;
		this->lucreaza = false;
		//static
		nrStudenti++;
		
	}

	Student(const char nume[], int varsta = 0, bool lucreaza = false) {
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->varsta = varsta;
		this->lucreaza = lucreaza;
		nrStudenti++;
		
		
	}

	//destructor
	~Student() {
		if (this->nume != NULL) {
			delete[] this->nume;
		}
	}
	//copy constr:
	Student(const Student& s) {
		//delete[] this->nume;
		this->varsta = s.varsta;
		this->lucreaza = s.lucreaza;
		//nu se pune nrStud
		if (s.nume != NULL) {
			this->nume = new char[strlen(s.nume) + 1];
			strcpy(this->nume, s.nume);
		}
		else {
			this->nume = NULL;
		}
	}

	//suprascriere operator =
	Student& operator=(const Student& s) {
		delete[] this->nume;
		//nu se pune nrStud
		this->varsta = s.varsta;
		this->lucreaza = s.lucreaza;
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		return *this;
	}
	int getVarsta() {
		return this->varsta;
	}
	char* getNumeGresit() {
		return this->nume;
	}
	char* getNumeCorect() {
		char* copie=new char[strlen(this->nume)+1];
		strcpy(copie, this->nume);
		//this->nume are zona separata de memorie fata de copie
		return copie;
	}
	bool getLucreaza() {
		return this->lucreaza;
	}
	void setLucreaza(bool varNouaLucreaza) {
		this->lucreaza = varNouaLucreaza;
	}

};

int Student::nrStudenti = 0;
/**/
//transmit valoare || adresa(pointer) || referinta
void incepeJob1(Student s) {
	s.setLucreaza(true);

}
void incepeJob2(Student* s) {
	(*s).setLucreaza(true);

}
void incepeJob3(Student& s) {
	s.setLucreaza(true);

}
void main() {
	Student s1;
	cout << "\nNrStud="<<Student::nrStudenti<<endl;
	Student s2("Mada", 20,false);

	cout << "\ns1.getNumeGresit(): " << s1.getNumeGresit();
	char* varGetNumeS1Gresit = s1.getNumeGresit();
	cout << "\nvarGetNumeS1Gresit: " << varGetNumeS1Gresit;

	strcpy(varGetNumeS1Gresit, "Ana");
	cout << "\nvarGetNumeS1Gresit dupa modif: " << varGetNumeS1Gresit;
	cout << "\ns1.getNumeGresit() dupa modif: " << s1.getNumeGresit();

	cout << "\n\ns2.getNumeCorect(): " << s2.getNumeCorect();
	char* varGetNumeS2Corect = s2.getNumeCorect();
	cout << "\n\nvarGetNumeS2Corect: " << varGetNumeS2Corect;
	strcpy(varGetNumeS2Corect, "Maria");
	cout << "\n\nvarGetNumeS2Corect dupa modifc: " << varGetNumeS2Corect;
	cout << "\n\ns2.getNumeCorect()dupa modifc: " << s2.getNumeCorect();

	int x = s2.getVarsta();
	x = 10;//nu se modifica s2.varsta


	Student s3;//se apl contr fara param
	Student* ps=new Student("Maria",20);
	incepeJob1(s3);
	cout << "\nS3.lucreaza= " << s3.getLucreaza();
	incepeJob1(*ps);
	cout << "\nps.lucreaza= " << (*ps).getLucreaza();

	//incepeJob2(&s3);
	//cout << "\nS3.lucreaza= " << s3.getLucreaza();
	//incepeJob2(ps);
	//cout << "\nps.lucreaza= " << (*ps).getLucreaza();

	incepeJob3(s3);
	cout << "\nS3.lucreaza= " << s3.getLucreaza();
	incepeJob3(*ps);
	cout << "\nps.lucreaza= " << (*ps).getLucreaza();

	cout << "\nNrStud=" << s1.nrStudenti << endl;
	cout << "\nNrStud=" << s2.nrStudenti << endl;
	cout << "\nNrStud=" << s3.nrStudenti << endl;

	_CrtDumpMemoryLeaks();
}