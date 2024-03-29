// CV07_matice_st49669.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matice.h"
#include <iostream>
#include <stdexcept>

using namespace std;


int main()
{
	try {
		Matice<int> m{ 3,3 };
		cout << "1. inicializace:" << endl;
		m.Vypis();
		int jednodpole[] = { 0,1,2,3,4,5,6,7,8 };
		m.NastavZ(jednodpole);
		cout << "Nastaveni prvku:" << endl;
		m.Vypis();
		Matice<int> mt = m.Transpozice();
		cout << "Transpozice:" << endl;
		mt.Vypis();
		Matice<int> mmt = m.Soucin(mt);
		cout << "Soucin:" << endl;
		mmt.Vypis();
		Matice<double> mmt_d = mmt.Pretypuj<double>();
		cout << "Pretypovani INT matice na DOUBLE:" << endl;
		mmt_d.Vypis();
		Matice<double> n_d{ 3,3 };
		double jednodpole_d[] = { 4.5,5,0,2,-0.5,7,1.5,9,6 };
		cout << "Naplneni dalsi nove DOUBLE matice:" << endl;
		n_d.NastavZ(jednodpole_d);
		n_d.Vypis();
		Matice<double> mmtn_d = mmt_d.Soucin(n_d);
		cout << "Soucin pretypovane DOUBLE a nove DOUBLE matice:" << endl;
		mmtn_d.Vypis();
		Matice<int> r = mmtn_d.Pretypuj<int>();
		cout << "Pretypovani predchoziho vysledku zpet na INT:" << endl;
		r.Vypis();
		Matice<int> t{ 3,3 };
		int tpole[] = { 85,225,236,292,819,866,499,1413,1496 };
		t.NastavZ(tpole);

		cout << "Porovnani kontrolni matice s vysledkem." << endl;
		cout << "Kontrolni:" << endl;
		t.Vypis();
		cout << "Vysledna:" << endl;
		r.Vypis();

		cout << "r==t ? " << (r.JeShodna(t) ? "true" : "false") << endl;
	}
	catch (const out_of_range &e){
		cerr << e.what() << endl;
	}
	catch (const invalid_argument &e) {
		cerr << e.what() << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}

