#ifndef __TABLE_H
#define __TABLE_H

#include "stdafx.h"
#include "platform.h"
#include "TableIterator.h"

#include <iostream>

//Tabulka
class DLL_SPEC Table {
public:
	Table(std::string table, FieldObject** fieldObjs, int fieldsTotal, std::string database);

	~Table();

	// Vloení nového øádku do tabulky (pole Object* (pro jednotlivé hodnoty sloupeèkù))
	void insert(Object** row);
	// Smazání vyrabného øádku z tabulky
	void remove(int rowid);

	// Select – vytvoøí iterátor k procházení tabulky
	Iterator* select();

	// Commit – pøenese zmìny z pamìti do datovıch souborù
	void commit();

	// Uzavøe tabulku (dealokuje pamìové prostøedky)
	void close();

	// Vrací poèet øádkù v tabulce
	int getRowCount() const;

	// Vrací pole FieldObject* popisující sloupeèky tabulky
	FieldObject** getFields() const;

	// Vrací poèet sloupeèkù
	int getFieldCount() const;

private:
	Object ***data;
	int dataRowsTotal = 0;
	std::string table;
	int rowsTotal = 0;
	FieldObject **fieldObjs;
	int fieldsTotal = 0;
	std::string database; //nutne pro commit, aby slo rozlisit misto ukladani

	void allocMoreRows(); //alokuje pocetRadku*2, volat POUZE, kdyz dataRowsTotal == rowsTotal
	void deallocData();
};

#endif