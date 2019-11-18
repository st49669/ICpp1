#ifndef _OSOBA_H
#define _OSOBA_H

#include <string>

using namespace std;


namespace Entity {
	class Osoba {
	private:
		string _jmeno;
		string _telefon;
		int _id;

	public:
		Osoba() {};
		Osoba(string jmeno, string telefon, int id);
		string GetJmeno() const;
		string GetTelefon() const;
		int GetId() const;
		string ToString() const;
	};
}

#endif