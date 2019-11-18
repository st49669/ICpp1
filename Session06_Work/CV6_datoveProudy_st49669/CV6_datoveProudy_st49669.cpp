
#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <ostream>
#include <sstream>
#include "Osoba.h";
#include "Adresa.h";
#include "Datum.h";

#define OSOB 5

using namespace std;

void ulozOsoby(Osoba** osoby) {
	ofstream ofs{};

	ofs.open("osoby.txt");

	if (ofs.is_open()) {
		for (int i = 0; i < OSOB; i++) {
			ofs << *osoby[i];
		}
		ofs.close();
	}
	else {
		throw logic_error("Do souboru osoby.txt nebylo mozne zapsat...");
	}

}

void nactiOsoby(Osoba** osoby) {
	ifstream ifs{};

	ifs.open("osoby.txt");

	if (ifs.is_open()) {
		for (int i = 0; i < OSOB; i++) {
			ifs >> *osoby[i];
		}
		ifs.close();
	}
	else {
		throw logic_error("Nacitani ze souboru osoby.txt se nezdarilo...");
	}

	
}

void vypisOsoby(Osoba** osoby) {
	for (int i = 0; i < OSOB; i++) {
		cout << *osoby[i];
	}
}

int main()
{
	Osoba** osoby = new Osoba*[OSOB];

	try {
		for (int i = 0; i < OSOB; i++) {
			osoby[i] = new Osoba("Jan" + to_string(i), "Novy" + to_string(i), 
				Adresa("Dlouha" + to_string(i), "Mesto" + to_string(i), 50000 + i), 
				Datum(i + 1, i + 2, 1990 + i));
		}
		vypisOsoby(osoby);
		ulozOsoby(osoby);
		delete[] osoby;
		osoby = new Osoba*[OSOB];
		nactiOsoby(osoby); //nefunkcni - nevim, jak zpracovat data ze streamu
		//vypisOsoby(osoby);
	}
	catch (const logic_error &e) {
		cerr << e.what() << endl;
	}
	catch (const invalid_argument &e) {
		cerr << e.what() << endl;
	}
	delete[] osoby;
	system("pause");
	return(0);
}

