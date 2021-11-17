#include<iostream>
using namespace std;

class Student {
private:
	char* nume;
	int varsta;

public:
	static int nrStudenti;

	Student() {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->varsta = 0;
		nrStudenti++;
	}
	Student(const char* nume,int varsta) {
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->varsta = varsta;
		nrStudenti++;
	}
	//constr copiere
	Student(const Student&s) {
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		this->varsta = s.varsta;
		nrStudenti++;
	}
	//op
	Student& operator=(const Student& s) {
		if (this->nume != NULL) {
			delete[] this->nume;
		}
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		this->varsta = s.varsta;
		return *this;
	}
	int suma(int a, int b) {
		return a + b;
	}
	//destr
	~Student() {
		if (this->nume != NULL) {
			delete[] this->nume;
		}
	}
	//functii friend | cls friend
	//++a a=1+a
	//b++ b=b+1;
	//a=b=c;
	//a++ ++;// in cascada
	friend const Student& operator++(Student&);
	friend const Student operator++(Student&,int);

	friend ostream& operator<<(ostream&,Student);
	friend istream& operator>>(istream&, Student&);

	//[]
	char operator[](int i) {
		if (this->nume != NULL && (i>=0 && i<strlen(this->nume))){
			return this->nume[i];
		}
		return '-';
	}

};
int Student::nrStudenti = 0;

const Student& operator++(Student& s) {
	//friend = accesam private protected
	s.varsta++;
	return s;
}
const Student operator++(Student& s, int i) {//operator--
	Student copie = s;//constr copiere
	//modifica s 
	s.varsta++;
	//return s(nemodificat);
	return copie;
}

ostream& operator<<(ostream& out, Student s) {
	out << "\nStudent: " << s.nume << " varsta: " << s.varsta;
	return out;
}
istream& operator>>(istream& in, Student& s) {
	//char nume[20];
	//cin >> nume;
	cout << "\n--> Nume:";
	string buffer;//String new | delete
	in >> buffer;
	if (s.nume != NULL) {
		delete[] s.nume;
	}
	s.nume = new char[buffer.length() + 1];
	strcpy_s(s.nume, buffer.length()+1,buffer.c_str());

	cout << "\n--> Varsta:";
	in >> s.varsta;
	return in;
}
int main() {
	Student s1;

	Student s2("Mada",20);
	Student s3 = s1;//Student s3(s1);
	Student s4;
	s4 = s2;//s4.operator=(s2)
	//s4.suma(2, 3);

	//++
	int a = 2;
	int b = 2;
	int c = ++a;//pre a=1+a
	int d = b++;//post b=b+1

	cout << "\na=" << a;
	cout << "\nb=" << b;
	cout << "\nc=" << c;
	cout << "\nd=" << d;
//	printf("Ana");
	//a=2 |3
	//b=2 |3
	//c=3 |3
	//d=2 |2
	Student s5=s1++;
	Student s6 = ++s2;
	cout <<s1 ;//cout.operator<<(char)
	cout << "\nCitire stud s1:";
	cin>>s1;
	cout << s1;
	cout<<"\nAfiseaza initiala nume: "<<s1[0];
	return 0;

	//+
	//a+b  = b+a 
	// s1+2 != 2+s1 != s1+s2
 
}