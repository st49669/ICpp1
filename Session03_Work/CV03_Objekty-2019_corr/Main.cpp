// CV03_Objekty-2019_corr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Objekt.h"
#include "StatickyObjekt.h"
#include "PohyblivyObjekt.h"
#include "Hra.h"

#include <iostream>
#include <string>
#include <ctime>


using namespace std;

double nahodnyDouble(double min, double max)
{
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}

StatickyObjekt* vytvorNahodnyStatObjekt(int id) {
	StatickyObjekt* o = new StatickyObjekt(id,TypPrekazky::Skala);
	o->SetX(nahodnyDouble(-1000.0, 1000.0));
	o->SetY(nahodnyDouble(-1000.0, 1000.0));
	return o;
}

PohyblivyObjekt* vytvorNahodnyPohObjekt(int id) {
	PohyblivyObjekt* o = new PohyblivyObjekt(id);
	o->SetX(nahodnyDouble(-1000.0, 1000.0));
	o->SetY(nahodnyDouble(-1000.0, 1000.0));
	o->SetUhelNatoceni(nahodnyDouble(0.0, (2 * 3.1415)));
	return o;
}

void vypisId(int* id, int size) {
	cout << "Vypis ID objektu: ";
	for (int i = 0; i < size; i++) {
		cout << id[i] << "\t";
	}
	cout << endl << endl;
}

void vypisId(Objekt** o, int size) {
	cout << "Vypis ID objektu: ";
	for (int i = 0; i < size; i++) {
		cout << o[i]->GetID() << "\t";
	}
	cout << endl << endl;
}

int main()
{

	srand(time(0)); //nahodny seed pro generator nah. cis. na zaklade systemoveho casu

	int ids = 101;
	Hra* hra = new Hra();
	try {
		for (int i = 0; i < 20; i++) {
			hra->VlozObjekt(vytvorNahodnyPohObjekt(ids));
			ids++;
			hra->VlozObjekt(vytvorNahodnyPohObjekt(ids));
			ids++;
			hra->VlozObjekt(vytvorNahodnyStatObjekt(ids));
			ids++;
		}



		int* idStatObj = hra->NajdiIdStatickychObjektu(-400.0, 700.0, -900.0, 600.0);
		PohyblivyObjekt** pohObjekty = hra->NajdiPohybliveObjektyVOblasti(0.0, 150.0, 750.0);
		PohyblivyObjekt** pohObjektyOtocene = hra->NajdiPohybliveObjektyVOblasti(0.0, 150.0, 750.0, 0.0, 3.1415);

		int nalStatObj = hra->NalezenoStatickychObjektu;
		int nalPohObj = hra->NalezenoPohyblivychObjektu;
		int nalPohObjOtocenych = hra->NalezenoPohyblivychObjektuSpravneOtocenych;

		cout << "Nalezeno stat. obj.: " << nalStatObj << endl;
		vypisId(idStatObj, nalStatObj);
		cout << "Nalezeno poh. obj.: " << nalPohObj << endl;
		vypisId((Objekt**)pohObjekty, nalPohObj);
		cout << "Nalezeno poh. obj. spravne otocenych: " << nalPohObjOtocenych << endl;
		vypisId((Objekt**)pohObjektyOtocene, nalPohObjOtocenych);

		delete idStatObj;
		delete[] pohObjekty;
		delete[] pohObjektyOtocene;
	}
	catch (const std::out_of_range &e) {
		cerr << e.what() << endl;
	}
	catch (const std::length_error &e) {
		cerr << e.what() << endl;
	}
	
	delete hra;
	system("PAUSE");
    return 0;
}

