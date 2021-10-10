#include<iostream>
#include<stdio.h>
using namespace std;

void oglindit(int nr, int x) {
	//int x = 0;
	while (nr) {
		x = x * 10 + nr % 10;
		nr /= 10;
	}
//	return x;
}

void main() {

	int valCautata = 3;
	bool gasit = false;
	int v[] = { 0,2,4,6,8 };
	//v[5] = 10;//eroare
	for (int i = 0; i < 5; i++) {
		if (v[i] == valCautata) {
			cout << i;
			gasit = true;
			i = 5;
			break;
		}
	}
	if (gasit == false) {
		cout << -1;
	}
	cout << endl <<"Int= "<< sizeof(int);
	cout << endl << "Float= " << sizeof(float);
	cout << endl << "Double= " << sizeof(double);
	cout << endl << "Long= " << sizeof(long);
	cout << endl << "Long long= " << sizeof(long long);

	cout << endl << "Char= " << sizeof(char);
	cout << endl << "Bool= " << sizeof(bool);

	//int n = 10;
	//int m = 0;
	//cout << n / m;

	int numar = 1234;
	int s = 0;
	oglindit(numar, s);
	cout << s;

}