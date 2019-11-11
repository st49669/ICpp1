#include "stdafx.h"
#include "Cas.h"

#include <stdexcept>



	Cas::Cas(int hod, int min, int sec) {
		if ((0 <= hod && hod <= 23) &&
			(0 <= min && min <= 59) &&
			(0 <= sec && sec <= 59))
		{
			this->hodiny = hod;
			this->minuty = min;
			this->sekundy = sec;
		}
		else {
			throw std::invalid_argument("Zadany cas je neplatny, pouzivam vychozi cas 12:00:00.");
		}
	}

	Cas::~Cas() {

	}

	int Cas::CompareTo(IComparable* obj) const {
		Cas* obj1 = dynamic_cast<Cas*>(obj);

		if (!dynamic_cast<Cas*>(obj1))
		{
			throw invalid_argument("Nelze porovnavat, objekt v parametru neni ze tridy Cas...");
		}

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
		return 10; //sem program nikdy nedojde
	}

	std::string Cas::ToString() const  {

		std::string ret = "{" + to_string(this->hodiny);
		ret += " hodin; " + to_string(this->minuty);
		ret += " minut; " + to_string(this->sekundy);
		ret += " sekund}\n";
			
		return ret;
	}
