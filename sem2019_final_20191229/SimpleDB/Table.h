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

	// Vlo�en� nov�ho ��dku do tabulky (pole Object* (pro jednotliv� hodnoty sloupe�k�))
	void insert(Object** row);
	// Smaz�n� vyrabn�ho ��dku z tabulky
	void remove(int rowid);

	// Select � vytvo�� iter�tor k proch�zen� tabulky
	Iterator* select();

	// Commit � p�enese zm�ny z pam�ti do datov�ch soubor�
	void commit();

	// Uzav�e tabulku (dealokuje pam�ov� prost�edky)
	void close();

	// Vrac� po�et ��dk� v tabulce
	int getRowCount() const;

	// Vrac� pole FieldObject* popisuj�c� sloupe�ky tabulky
	FieldObject** getFields() const;

	// Vrac� po�et sloupe�k�
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