#include "stdafx.h"
#include <cstdio> //C++ varianta knihovny stdio.h, ted neni potreba
#include <iostream> //pro proudy jako cin a cout, ted se hodi
using namespace std;


struct Trojuhelnik {
	int a, b, c;
} t;

bool lzeSestrojit(Trojuhelnik* t) {
	int a = t->a, b = t->b, c = t->c;
	if ((a + b > c) && (a + c > b) && (b + c > a)) {
		return true;
	}
	return false;
}

int main()
{
	int poc;
	cout << "Zadej, kolik chces trojuhelniku: "; //proud na vystup
	cin >> poc; //proud ze vstupu
	Trojuhelnik* ukazatel = new Trojuhelnik[poc]; //alokace pameti jako pole ukazatelu

	for (int i = 0; i < poc; i++) {
		cout << endl << "Trojuhelnik c. " << i + 1 << endl;
		cout << "Zadej stranu A: ";
		cin >> ukazatel[i].a;
		cout << "Zadej stranu B: ";
		cin >> ukazatel[i].b;
		cout << "Zadej stranu C: ";
		cin >> ukazatel[i].c;
	}

	for (int i = 0; i < poc; i++) {
		int a = ukazatel[i].a, b = ukazatel[i].b, c = ukazatel[i].c;

		if (lzeSestrojit(&ukazatel[i])) {
			cout << endl << "Zadane rozmery trojuhelniku cislo " << i+1 << " jsou platne" << endl;
			cout << "Obvod: " << a + b + c << endl;
		}
		else {
			cout << endl << "Neplatne rozmery trojuhelniku cislo " << i + 1 << endl;
		}
	}

	delete[] ukazatel;
	system("pause");
    return 0;
}
