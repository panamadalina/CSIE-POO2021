#include<iostream>
using namespace std;

class A {
public:
	int x() {
		return 0;
	}
};
class B {
public:
	int x() {
		return 2;
	}
	int y() {
		return 1;
	}
};
class C:public A, public B {

};

class Persoana {
public: 
	//nume
	//varsta
	int x;
};

class Student :public Persoana {
	// facultate
	//bursa
};

class Angajat :public Persoana {
	//salariu
	//companie

};

class Batran :public Angajat, public Student {
	//pensie
};
/*-------------------------------------------------*/
class Salariat {
public:
	int salariu;
	Salariat() {
		salariu = 0;
	}
};

class Manager :virtual public Salariat {
	//subalterni
public:
	Manager() {
		salariu = 100;
	}
};
class Profesor :virtual public Salariat {
	//studenti
public:
	Profesor() {
		salariu = 50;
	}
	
};

class Individ :public Manager, public Profesor {
	//spor ca munceste f mult
};
//polimorfim
class Pasare {
public:
	virtual void zboara2() = 0;//>= 1 functie virtuala pura ->clasa pasare cls abstracta 
	virtual void zboara() {//fctie virtuala
		cout << " \n-> zboara";
	}
};
class Vultur :public Pasare {
	 void zboara2() {
		 //fa ceva 1
		 //
	}
};

class Pinguin : public Pasare {
public:
	void zboara2() {
		//fa ceva 2
	}
	void zboara() {
		cout << " \n-> nu zboara";
	}
};

int main() {
	
	C cInstanta;
	cout<<cInstanta.B::x();//probl de amiguitate->mostenire multipla
//	cout <<endl<< cInstanta.y();
	A aInstanta;
	/*aInstanta.C::x();*/

	//upcasting
	//batran -> angajat
	Angajat ang;
//	Batran batran;
//	ang = batran;//se pierde informatie

	Persoana pers;
	//pers = batran;//nu merge-> upcasting pe mai multe nivele

	//upcasting etapizat
	//pers = ang;// pers=batran || ang=batran-> pers=ang

	//downcasting nu merge ca in acest caz:
	//int =2 -> float 2.00 

	//mostenire dubla a radacinii
	cout << endl << endl;
	Individ individ;
	cout<<individ.Profesor::salariu<<endl;
	cout << individ.Manager::salariu;
	//virtuale->unice
	Salariat salariat;
	salariat = individ;//upcasting direct -> virtual


	//polimorfism
	//1. Overloading -> functii -> int suma(int a, int b)  ->  int  suma(int a, float b)
	//sum(2,3) si suma(2,3.4)

	//2. override -> clase
	Vultur vultur;
	cout << "Vultur:";
	vultur.zboara();

	Pinguin pinguin;
	cout << "\n Pinguin:";
	pinguin.zboara();

	cout << endl;
	Pasare* p = new Pinguin();
	//Pasare p;->nu merge
//Clasa pasare are o fctie vrituala 
//=> pasare e cls abstracta
//-> nu putem instantia un obj
//-> putem folosi doar pointer!

	cout << "\n Pinguin2:";
	p->zboara();

	cout << endl << endl;
	
	return 0;

}