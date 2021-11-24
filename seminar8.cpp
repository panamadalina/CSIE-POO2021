#include<iostream>
using namespace std;

class Student {
private:
	char* nume;
	int varsta;
	bool lucreaza;

public:
	static int nrStudenti;

	Student() {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->varsta = 0;
		this->lucreaza = false;
		nrStudenti++;
	}
	Student(const char* nume, int varsta, bool lucreaza = false) {
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->varsta = varsta;
		this->lucreaza = lucreaza;
		nrStudenti++;
	}
	Student(const Student& s) {
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		this->varsta = s.varsta;
		this->lucreaza = s.lucreaza;
		nrStudenti++;
	}
	Student& operator=(const Student& s) {
		if (this->nume != NULL) {
			delete[] this->nume;
		}
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		this->varsta = s.varsta;
		this->lucreaza = s.lucreaza;
		return *this;
	}
	~Student() {
		if (this->nume != NULL) {
			delete[] this->nume;
		}
	}

	friend ostream& operator<<(ostream&, Student);
	friend istream& operator>>(istream&, Student&);

	void operator!() {
		this->lucreaza = !this->lucreaza;
	}

	void setLucreaza(bool luc) {
		this->lucreaza = luc;
	}
	bool operator!=(Student s) {// Ana vs Ana
		if (this->varsta == s.varsta && this->lucreaza == s.lucreaza && strcmp(this->nume, s.nume) == 0) {
			return false;
		}
		else {// this->varsta!=s.varsta || this->lucreaza!=s.lucreaza || strcmp()!=0
			return true;
		}
	}

	Student& operator+=(int varstaSuplimentara) { //s1.operator+=(2)
		this->varsta += varstaSuplimentara;
		return *this;
	}

    Student operator+(int varstaSupl ) {  //s3= val ->       s1.operator+(2) // s3-modif s1- nemodif
		
		Student copie = *this;
		copie.varsta += varstaSupl;
		return copie; //( =*this);
	////	this->varsta += varstaSupl;
	}
	//s3=2+s1;//s3.operator=(   2.operator+(s1)   )
	//s3 = s1+2

	friend Student operator+(int,Student s);

    operator int() {//s1.operatorInt()
		return this->varsta;
	}
	//operator char*() {
	//	return this->nume;
	//}
};
int Student::nrStudenti = 0;

ostream& operator<<(ostream& out, Student s) {
	out << "\nStudent: " << s.nume << " varsta: " << s.varsta;
	if (s.lucreaza) {
		out << " - lucreaza";
	}
	else {
		out << " - nu lucreaza";
	}
	return out;
}
istream& operator>>(istream& in, Student& s) {
	cout << "\n--> Nume:";
	string buffer;//String new | delete
	in >> buffer;
	if (s.nume != NULL) {
		delete[] s.nume;
	}
	s.nume = new char[buffer.length() + 1];
	strcpy_s(s.nume, buffer.length() + 1, buffer.c_str());

	cout << "\n--> Varsta:";
	in >> s.varsta;
	cout << "\n--> Lucreaza?";
	in >> s.lucreaza;
	return in;
}

Student operator+(int varstaSupl, Student s) {//s3= 2+s1 //s3.operator=(   2.operator+(s1)   )
	s.varsta += varstaSupl;
	return s;
	
}

int main() {
	Student s1;
	Student s2("Mada",20);
	//s2 = s1; // s2.operator=(s1) 

	//Op !
	//int i = -2;
	//!i;
	cout << "\n-->Op !\n";
	cout << s1; // -> cout.operator<<(s1)
	!s1;// s1.operator!()=>s1
	cout << s1;
	s1.setLucreaza(true);
	

	//Op !=
	//if(a!=b)
	cout << "\n-->Op !=\n";
	if (s1 != s2) {//s1.operator!=(s2)
//r1 => true | !=0 | !=NULL
		cout << "\nStudenti diferiti";
	}
	else {
		//r2
		cout << "\nStudenti identici";
	}

	//+=
	cout << "\n-->Op +=\n";
	int i = 2;
	i += 2;// i=i+2 //
	
	cout << s1;
	s1 += 2;//s1.operator+=(2)
	cout << s1;

	//OP +
	cout << "\n-->Op +=\n";
	int a = 2; // 6
	int b = 3; //3
	cout << "\n" << a << " - " << b;
	a = b + 3; // 3+b
	cout << "\n" << a << " - " << b;
	Student s3;
	cout << s3;
	s3 = s2 + 3; //s3.operator=(s1.operator+(3))
	cout << s3;
	cout << s2;
	s3 = 2 + s2;//
	cout << "\n + var 2";
	cout << s3;
	cout << s2;
	//op cast:
	//float a = 10.2;
	//int x = 10;
	//x = 12 + a;//12+10=22

	int varstaRez = 3 +s1;// s1.operatorInt()
	cout << varstaRez;
	return 0;

}