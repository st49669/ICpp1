// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Pokladna.h"

using namespace std;


int main()
{
	Pokladna* pokl = new Pokladna;
	
	pokl->vystavUctenku(12.05, 24);
	pokl->vystavUctenku(31.99, 20);
	pokl->vystavUctenku(109.99, 15);
	pokl->vystavUctenku(84.99, 21);

	Uctenka* u = new Uctenka[4];

	u[0] = pokl->dejUctenku(1000);
	u[1] = pokl->dejUctenku(1001);
	u[2] = pokl->dejUctenku(1002);
	u[3] = pokl->dejUctenku(1003);

	cout << "Kontrola naplneni uctenek: CisloUctenky;CastkaBezDph;Dph" << endl;

	for (int i = 0; i < 4; i++) {
		cout << "Uctenka "<<i+1<<".: "<< u[i].getCislo() << ";" << u[i].getCastka() << ";" << u[i].getDph() << endl;
	}
	
	cout << endl << "Celkova castka bez DPH: " << pokl->dejCastku() << endl;
	cout << "Celkova castka s DPH: " << pokl->dejCastkuVcDph() << endl;

	delete[] u;
	delete pokl;
	
	system("pause");
    return 0;
}

