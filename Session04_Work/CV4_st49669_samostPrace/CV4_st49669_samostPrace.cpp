// CV4_st49669_samostPrace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "IComparable.h"

using namespace std;


struct Cas : IComparable {
private:
	int hodiny = 3;
	int minuty = 3;
	int sekundy = 3;

public:
	Cas(int hod, int min, int sec) {
		if (0 <= hod && hod <= 23) {
			this->hodiny = hod;
		}
		if (0 <= min && min <= 59) {
			this->minuty = hod;
		}
		if (0 <= sec && sec <= 59) {
			this->sekundy = hod;
		}
	}

	virtual ~Cas() {

	}

	int compareTo(IComparable* obj) const {
		Cas* obj1 = (Cas *)obj;

		int hod = obj1->hodiny;
		int min = obj1->minuty;
		int sec = obj1->sekundy;
		if (hod == this->hodiny) {

			if (min == this->minuty) {
				if (sec == this->sekundy) {
					return 0;
				}
				else if (sec > this->sekundy) {
					return -1;
				}
				else {
					return 1;
				}
			}
			else if (min > this->minuty) {
				return -1;
			}
			else {
				return 1;
			}

		}
		else if (hod > this->hodiny) {
			return -1;
		}
		else if (hod < this->hodiny) {
			return 1;
		}
		return 10;
	}

	string toString(IComparable* obj) const {
		return obj->ToString();
	}

};


int main()
{
	int pocet = 10;
	IComparable** icom = new IComparable*[pocet];

	for (int i = 0; i < pocet; i++) {
		icom[i] = new Cas(1, 2, 3); //TODO: random generator
	}

	system("pause");
    return 0;
}

