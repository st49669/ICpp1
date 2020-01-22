#ifndef _TABLELIST_H
#define _TABLELIST_H

#include "helpful.h"
#include <iostream>

class TableList {
public:
	TableList() : _first(nullptr) {};
	~TableList();
	void add(std::string name, Table *table); //pridat tabulku na konec ADS singly linked list
	Table *getTableByName(std::string name); //tabulka dle nazvu, vraci nullptr, pokud nenalezena
	void printTableList(); //zakladni tisk seznamu tabulek
	void commitAll(); //commit na vsech tabulkach
	void closeAll(); //close na vsech tabulkach
private:
	struct LinkedList { //struktura prvku ADS singly linked list
		LinkedList(std::string name, Table *table) : name(name), table(table) {};
		std::string name;
		Table *table;
		LinkedList *next = nullptr;
	};
	LinkedList *_first = nullptr; //prvni prvek ADS
};

#endif

