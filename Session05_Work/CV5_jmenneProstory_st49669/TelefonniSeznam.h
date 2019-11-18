#ifndef _TELEFONNISEZNAM_H
#define _TELEFONNISEZNAM_H

#include <string>
#include "Osoba.h"

using namespace std;

namespace Model {
	

	class TelefonniSeznam {
	private:
		struct SpojovySeznam {
			SpojovySeznam(Entity::Osoba osoba);
			SpojovySeznam() {};
			Entity::Osoba data;
			SpojovySeznam *dalsi;
		};
		SpojovySeznam *_prvni;
	public:

		TelefonniSeznam() : _prvni(nullptr) {};
		~TelefonniSeznam();
		string NajdiCislo(string jmeno) const;
		string NajdiCislo(int id) const;
		void PridejOsobu(Entity::Osoba osoba);
		string ToString() const;
	
	};
}

#endif

