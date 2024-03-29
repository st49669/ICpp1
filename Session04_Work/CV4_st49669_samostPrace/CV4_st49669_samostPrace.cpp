

#include "stdafx.h"
#include <string>
#include <iostream>
#include <ctime>
#include "Cas.h"
#include "IComparable.h"

#define POCET 15

using namespace std;

int nahodnyInt(int min, int max)
{
	return min + rand() % ((max + 1) - min);
}

void razeniVkladanim(IComparable** casy, int velikost) {
	if (velikost < 1) {
		throw length_error("Nelze radit pole casu bez prvku...");
	}
	for (int i = 0; i < velikost - 1; i++) {
		int j = i + 1;
		IComparable* tmp = casy[j];
		while (j > 0 && tmp->CompareTo(casy[j - 1]) == 1) {
				casy[j] = casy[j - 1];
				j--;
		}
		casy[j] = tmp;
	}
}



int main()
{
	int vytvoreno = 0;
	IComparable** icom = new IComparable*[POCET];

	srand(time(NULL)); //seed pro nahodny generator

	try {
		cout << "Vytvarim nastaveny pocet casu: " << endl;
		for (int i = 0; i < POCET; i++) {
			icom[i] = new Cas(nahodnyInt(0, 23), nahodnyInt(0, 59), nahodnyInt(0, 59));
			vytvoreno++;
			cout << icom[i]->ToString();
		}

		cout << "Vytvoreno casu celkem: " << vytvoreno << endl << endl;
		/*for (int i = 0; i < POCET-1; i++) { // Testovac porovnani
			cout << "Porovnani: " << icom[i]->CompareTo(icom[i + 1]) << endl;
		}*/ 
		cout << "Nasleduje pokus o serazeni casu: " << endl;

		razeniVkladanim(icom, vytvoreno);

		for (int i = 0; i < POCET; i++) {
			cout << icom[i]->ToString();
		}

	}
	catch (const std::invalid_argument &e) {
		cerr << e.what() << endl;
	}

	catch (const std::length_error &e) {
		cerr << e.what() << endl;
	}

	delete[] icom; //dealokace

	system("pause");
    return 0;
}

