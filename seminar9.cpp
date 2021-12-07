#include<iostream>
#include <fstream>
using namespace std;

class Student {
private:
	string nume;
	int varsta;
	int nrNote = 0;
	int* note = nullptr;

public:
	static int nrStudenti;

	Student() {
		this->nume = "Anonim";
		this->varsta = 0;
		nrStudenti++;
	}
	Student(const string nume, int varsta, int nrNote, int* note) {
		this->nume = nume;
		this->varsta = varsta;

		if (note != nullptr && nrNote > 0)
		{
			this->nrNote = nrNote;
			this->note = new int[nrNote];
			for (int i = 0; i < nrNote; i++)
			{
				this->note[i] = note[i];
			}
		}

		nrStudenti++;
	}
	Student(const Student& s) {
		this->nume = s.nume;
		this->varsta = s.varsta;
		if (s.note != nullptr && s.nrNote > 0)
		{
			this->nrNote = s.nrNote;
			this->note = new int[s.nrNote];
			for (int i = 0; i < s.nrNote; i++)
			{
				this->note[i] = s.note[i];
			}
		}
		nrStudenti++;
	}
	Student& operator=(const Student& s) {
		//if (this->nume != NULL) {
		//	delete[] this->nume;
		//}
		this->nume = s.nume;
		this->varsta = s.varsta;
		if (s.note != nullptr && s.nrNote > 0)
		{
			this->nrNote = s.nrNote;
			this->note = new int[s.nrNote];
			for (int i = 0; i < s.nrNote; i++)
			{
				this->note[i] = s.note[i];
			}
		}

		return *this;
	}
	//destr
	~Student() {
		/*	if (this->nume != NULL) {
				delete[] this->nume;
			}*/
	}

	friend ostream& operator<<(ostream&, Student);

	void serializare() {
		//
		ofstream f("student.bin", ios::binary);
		int length = this->nume.length();
		f.write((char*)&length, sizeof(length));

		f.write(this->nume.c_str(), length + 1);
		f.write((char*)&this->varsta, sizeof(this->varsta));
		f.write((char*)&this->nrNote, sizeof(this->nrNote));
		for (int i = 0; i < nrNote; i++) {
			f.write((char*)&this->note[i], sizeof(this->note[i]));
		}
		f.close();
	}
	void deserializare() {
		ifstream f("student.bin", ios::binary);
		int dimNume;
		f.read((char*)&dimNume, sizeof(int));
		char* aux = new char[dimNume + 1];
		f.read(aux, dimNume + 1);
		this->nume = aux;
		delete[] aux;//!
		f.read((char*)&this->varsta, sizeof(this->varsta));
	//	int dimNrNote;//!!!!
	//	f.read((char*)&dimNrNote, sizeof(dimNrNote));//!GRESIT!
		f.read((char*)&this->nrNote, sizeof(this->nrNote));//lipsise
		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++) {
			f.read((char*)&this->note[i], sizeof(this->note[i]));
		}

		f.close();
	}
};
int Student::nrStudenti = 0;



ostream& operator<<(ostream& out, Student s) {
	out << "\nStudent: " << s.nume << " - varsta: " << s.varsta << " - note: ";
	if (s.note != nullptr && s.nrNote > 0)
	{
		for (int i = 0; i < s.nrNote; i++)
		{
			out << s.note[i] << " ";
		}
	}
	return out;
}


int main() {
	Student s1;


	int note[] = { 10,8,9 };
	Student s2("Mada", 20, 3, note);
	s2.serializare();
	cout << s1;
	cout << s2;
	s1.deserializare();
	cout << "\nDupa deserializare:"<<s1;
	return 0;
}