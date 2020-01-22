#include "stdafx.h"
#include "Table.h"
#include <fstream>
#include <stdexcept>


Table::Table(std::string table, FieldObject** fieldObjs, int fieldsTotal, std::string database){
	this->table = table; //nazev - identifikace tabulky
	this->rowsTotal = 0; //pocet radku
	this->fieldObjs = fieldObjs; //popis sloupecku
	this->fieldsTotal = fieldsTotal; //pocet sloupecku
	this->database = database;
	this->data = nullptr;
}

Table::~Table() {
	for (size_t i = 0; i < fieldsTotal; ++i) {
		delete fieldObjs[i];
	}
	delete[] fieldObjs;

	deallocData(); //pri tomto pouziti je parametr celkem zbytecny...
}

void Table::insert(Object **row) {
	if (row == nullptr) throw std::invalid_argument("Cannot insert empty row.");

	if (rowsTotal == 0) { //prvni alkoace
		data = new Object **[1]; //alokuj pole radku s jednotlivymi sloupecky
		data[0] = new Object *[fieldsTotal]; //alokace urceneho poctu sloupcu na 1. radek
		++rowsTotal; // 1 radek
	} else if (rowsTotal == dataRowsTotal) { //nutnost pridani dalsich alokovanych radku
		allocMoreRows();
	}
	data[dataRowsTotal] = row;
	++dataRowsTotal;
}

void Table::remove(int rowid) {
	if (rowid < 0) throw std::out_of_range("This rowid is invalid: "+rowid);
	if (rowid >= dataRowsTotal) throw std::out_of_range("No such row exists (yet):" + rowid);

	data[rowid] = nullptr;
	if (rowid != (dataRowsTotal - 1)) { //nedoslo k odstraneni posledniho, takze nutnost preskupeni
		for (size_t i = rowid; i < dataRowsTotal - 1; ++i) {
			data[i] = data[i + 1];
		}
		data[dataRowsTotal - 1] = nullptr;
	}
	--dataRowsTotal;
}

Iterator* Table::select() {
	return new TableIterator(data, dataRowsTotal);
}

void Table::commit() {
	std::string fileName = "../databases/" + database + "/" + table + ".dbdat";
	std::ofstream ofs(fileName, std::ofstream::out);

	if (!ofs.is_open()) throw std::logic_error("Failed writing the table data file for table: " + table);

	ofs << dataRowsTotal << std::endl; //zapis poctu radku s daty
	for (size_t i = 0; i < dataRowsTotal; ++i) { //projit radky s daty
		for (size_t j = 0; j < fieldsTotal; ++j) { //projit vsechny sloupce
			if (data[i][j]->isType(FieldType::Integer)) { //sloupec je integer
				ofs << data[i][j]->getInt() << std::endl;
			} else if (data[i][j]->isType(FieldType::Double)) { //sloupec je double
				ofs << data[i][j]->getDouble() << std::endl;
			} else if (data[i][j]->isType(FieldType::String)) { //sloupec je string
				ofs << data[i][j]->getString().c_str() << std::endl;
			} else throw std::logic_error("Invalid field type, table cannot be written: " + table);
		} //end for (size_t j = 0; j < fieldsTotal; j++)
	} //end for (size_t i = 0; i < dataRowsTotal; i++)
	ofs.close();
}

void Table::close() {
	Table::~Table();
	this->table = "";
	this->dataRowsTotal = 0;
	this->fieldsTotal = 0;
	this->rowsTotal = 0;
}

int Table::getRowCount() const {
	return dataRowsTotal;
}

FieldObject** Table::getFields() const {
	return fieldObjs;
}

int Table::getFieldCount() const {
	return fieldsTotal;
}

void Table::allocMoreRows() { //POZOR: volat pouze, kdyz (rowsTotal == dataRowsTotal)!!!
	rowsTotal += rowsTotal; //1,2,4,8,16,... dle rady od Rezaniny
	Object ***newData = new Object **[rowsTotal]; //novy 2D pole o velikosti rowsTotal radku
	
	for (size_t i = 0; i < rowsTotal/2; i++) {
		newData[i] = new Object *[fieldsTotal];
		for (size_t j = 0; j < fieldsTotal; j++) {
			if (data[i][j]->isType(FieldType::Integer)) { //sloupec je integer
				newData[i][j] = new IntObject(data[i][j]->getInt());
			}
			else if (data[i][j]->isType(FieldType::Double)) { //sloupec je double
				newData[i][j] = new DoubleObject(data[i][j]->getDouble());
			}
			else if (data[i][j]->isType(FieldType::String)) { //sloupec je string
				newData[i][j] = new StringObject(data[i][j]->getString());
			}
		}
	}

	deallocData(); //dealokace prechozich dat, jsou uz prevedeny do noveho pole

	data = newData;
}

void Table::deallocData() {
	for (size_t i = 0; i < dataRowsTotal; ++i) {
		for (size_t j = 0; j < fieldsTotal; ++j) {
			delete data[i][j];
		}
		delete[] data[i];
	}
	delete[] data;
}

