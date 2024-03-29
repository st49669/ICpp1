
#include "stdafx.h"
#include <string>
#include <iostream>
#include "TelefonniSeznam.h";
#include "Osoba.h";

#define	OSOB	16

using namespace std;
using namespace Model;
using namespace Entity;


void VypisSeznam(TelefonniSeznam *ts) {
	cout << "Vypis telefonniho seznamu: " << endl;
	cout << ts->ToString() << endl;
}

void ZkouskaVyhledavani(TelefonniSeznam *ts) {
	cout << "Nasleduje zkouska vyhledavani (vsechna ID a jmena vzestupne): " << endl;
	for (int i = 0; i < OSOB; i++) {
		cout << ts->NajdiCislo(i) << " (podle ID)"<< endl;
		cout << ts->NajdiCislo("Jan Novy_" + to_string(i)) << " (podle jmena)" << endl;
	}
	cout << endl << "Hledam nesmysl: ";
	cout << ts->NajdiCislo("AAA") << endl;
}

int main()
{
	TelefonniSeznam* ts = new TelefonniSeznam();
	try {
		VypisSeznam(ts);
		for (int i = 0; i < OSOB; i++) {
			ts->PridejOsobu(Osoba("Jan Novy_" + to_string(i), "+42073300000" + to_string(i), i));
		}
		VypisSeznam(ts);
		ZkouskaVyhledavani(ts);
	}
	catch (const invalid_argument &e) {
		cerr << e.what() << endl;
	}
	catch (const logic_error &e) {
		cerr << e.what() << endl;
	}
	delete ts;
	system("pause");
    return 0;
}

