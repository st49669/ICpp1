#include "stdafx.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include "Db.h"
#include "platform.h"

Db *Db::open(std::string database) {
	Db *db = new Db(database);
	return db;
}

Db::Db(std::string database) {
	this->tablesTotal = 0;
	this->createdTablesTotal = 0;
	this->dbName = database;
	this->tables = nullptr;
	createDbDir(); //slozka pro ukladani databaze
}

Db::~Db() {
	if (tables != nullptr) delete[] tables;
}

bool Db::isTableCreatedOrLoaded(std::string table) const {
	if (tables == nullptr) return false;
	for (size_t i = 0; i < createdTablesTotal; ++i) {
		if (tables[i].compare(table)==0) return true;
	}
	return false;
}

void Db::addTableName(std::string table) {
	if (tables == nullptr) { //1. tabulka
		tables = new std::string[1];
		tablesTotal = 1;
	} else if (createdTablesTotal == tablesTotal) { //nutnost rozsireni pole nazvu tabulek
		tablesTotal += tablesTotal; //1,2,4,8,16,... dle rady od Rezaniny
		std::string *tablesNew = new std::string[tablesTotal];
		//kopirovani stareho seznamu do noveho
		memcpy(tablesNew, tables, createdTablesTotal * sizeof(std::string));
		delete[] tables; //vymazani stareho seznamu
		tables = tablesNew;
	}
	tables[createdTablesTotal] = table;
	++createdTablesTotal;
}

bool Db::tableSchemaFileExists(std::string table) const {
	std::string fileName = "../databases/" + dbName + "/" + table + ".dbsch";
	std::ifstream ifs(fileName.c_str());
	return ifs.good();
}

bool Db::tableDataFileExists(std::string table) const {
	std::string fileName = "../databases/" + dbName + "/" + table + ".dbdat";
	std::ifstream ifs(fileName.c_str());
	return ifs.good();
}

void Db::close() {
	Db::~Db();
}

Table *Db::createTable(std::string name, int fieldsCount, FieldObject **fields) {
	if (name.empty()) 
		throw std::invalid_argument("The table name is empty...");
	if (fieldsCount < 1 || fields == nullptr) 
		throw std::invalid_argument("Given field params are invalid or empty...");
	if (isTableCreatedOrLoaded(name)) 
		throw std::logic_error("This table already exists: " + name);

	Table *newTable = new Table(name, fields, fieldsCount, dbName);

	addTableName(name);

	std::string fileName = "../databases/" + dbName + "/" + name + ".dbsch";
	std::ofstream ofs{};
	ofs.open(fileName);

	if (!ofs.is_open()) throw std::logic_error("Failed writing the table schema file for table: " + name);
	
	ofs << fieldsCount << std::endl; //zapis poctu sloupecku
	for (size_t i = 0; i < fieldsCount; i++) {
		switch (fields[i]->getType()) { //zapis typu sloupecku
			case FieldType::Integer: 
				ofs << "I" << std::endl;
				break;
			case FieldType::Double:
				ofs << "D" << std::endl;
				break;
			case FieldType::String:
				ofs << "S" << std::endl;
				break;
			default:
				throw std::logic_error("Invalid column type in the schema of the table: " + name);
		}
		ofs << fields[i]->getName() << std::endl; //zapis nazvu sloupecu
	} //end for (size_t i = 0; i < fieldsCount; i++)
	ofs.close();
	return newTable;
}

Table *Db::openTable(std::string name) {
	if (name.empty())
		throw std::invalid_argument("The table name is empty...");
	if (!tableSchemaFileExists(name))  //musi existovat soubor se schematem
		throw std::invalid_argument("No such table found in database files: " + dbName);
	if (isTableCreatedOrLoaded(name)) //tabulka nesmi byt uz nactena
		throw std::logic_error("This table has already been opened: " + name);
	
	return loadTableSchemaFromFile(name);
}

Table *Db::openOrCreateTable(std::string name, int fieldsCount, FieldObject **fields) {
	if (name.empty()) 
		throw std::invalid_argument("The table name is empty...");
	if (isTableCreatedOrLoaded(name)) //tabulka nesmi uz byt nactena nebo vytvorena
		throw std::logic_error("This table has already been created or opened: " + name);

	if (tableSchemaFileExists(name)) { //je k dispozici schema tabulky?
		return openTable(name); //ano - ottevri ji
	}
	//jinak vytvorit tabulku
	return createTable(name, fieldsCount, fields);
}

Table *Db::loadTableSchemaFromFile(std::string name) {
	std::string fileName = "../databases/" + dbName + "/" + name + ".dbsch";
	std::ifstream ifs{};
	ifs.open(fileName.c_str());

	if (ifs.is_open()) { //mozna redundantni kontrola
		int numOfFields;
		std::string numOfFieldsStr;
		std::string fieldType;
		std::string fieldName;
		FieldObject **fieldsObjsToLoad;

		std::getline(ifs, numOfFieldsStr); //1. radek obsahuje pocet sloupcu
		numOfFields = stoi(numOfFieldsStr);

		fieldsObjsToLoad = new FieldObject *[numOfFields]; //inicializovat pocet sloupcu
		for(size_t i = 0; i < numOfFields; ++i) { //prochazet sloupce
			std::getline(ifs, fieldType);
			std::getline(ifs, fieldName);
			if (fieldType.compare("I") == 0) { //Intetger
				fieldsObjsToLoad[i] = new FieldObject(fieldName, FieldType::Integer);
			} else if (fieldType.compare("D") == 0) { //Double
				fieldsObjsToLoad[i] = new FieldObject(fieldName, FieldType::Double);
			} else if (fieldType.compare("S") == 0) { //String
				fieldsObjsToLoad[i] = new FieldObject(fieldName, FieldType::String);
			} else {
				throw std::logic_error("Invalid content of the schema file: " + fileName);
			}	
		}
		Table *newTable = new Table(name, fieldsObjsToLoad, numOfFields, dbName);
		addTableName(name);
		ifs.close();
		return loadTableDataFromFile(name, newTable);
	}

}

Table *Db::loadTableDataFromFile(std::string name, Table *emptyTable) {
	std::string fileName = "../databases/" + dbName + "/" + name + ".dbdat";
	std::ifstream ifs{};
	ifs.open(fileName.c_str());
	if (ifs.is_open()) { //kdyz neprojde, nevadi, schmema je uz nacteno...
		// POZOR na dodrzeni formatu z commmit:
		// 1. radek - je pocet radku tabulky
		// zbytek jsou hodnoty radek po radku
		int rowsCount = 0;
		std::string rowsCountStr;

		std::getline(ifs, rowsCountStr); //1. radek
		rowsCount = stoi(rowsCountStr);

		int columnsCount = emptyTable->getFieldCount();
		FieldObject **fieldObjs = emptyTable->getFields();
		
		for (size_t i = 0; i < rowsCount; ++i) { //radky
			Object** tableRow = new Object *[columnsCount]; //pripravit radek tabulky s poctem sloupcu
			for (size_t j = 0; j < columnsCount; j++) { //sloupce
				std::string currVal;
				std::getline(ifs, currVal);
				switch (fieldObjs[j]->getType()) { //jaky je typ sloupce, kam se nacita hodnota?
					case FieldType::Integer:
						tableRow[j] = Int(stoi(currVal));
						break;
					case FieldType::Double:
						tableRow[j] = Double(stod(currVal));
						break;
					case FieldType::String:
						tableRow[j] = String(currVal);
						break;
					default:
						throw std::logic_error("Data file structure is corrupted!");
				}
			} //end for (size_t j = 0; j < columnsCount; j++) - sloupce
			emptyTable->insert(tableRow);
		} //end for (size_t i = 0; i < rowsCount; i++) - radky
		ifs.close();
	} // end if
	return emptyTable;
}

void Db::createDbDir() const {
	std::string dbFolder = "..\\databases\\" + dbName + "\\";
	std::wstring path = std::wstring(dbFolder.begin(), dbFolder.end());
	_wmkdir(path.c_str());
}

Object *Db::Int(int value) {
	return new IntObject(value);
}

Object *Db::Double(double value) {
	return new DoubleObject(value);
}

Object *Db::String(std::string value) {
	return new StringObject(value);
}

FieldObject *Db::Field(std::string name, FieldType type) {
	return new FieldObject(name, type);
}