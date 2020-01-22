#ifndef __DBAPI_H
#define __DBAPI_H
#include "platform.h"
#include "Table.h"

// Databáze
class DLL_SPEC Db {
public:
	// Otevře databázi
	static Db* open(std::string database);
    // Uzavře databázi (dealokuje paměťové prostředky)
	void close();


	// Vytvoří novou tabulku
	Table* createTable(std::string name, int fieldsCount, FieldObject** fields);
	// Otevře existující tabulku
	Table* openTable(std::string name);
	// Otevře tabulku (pokud neexistuje, vytvoří automaticky novou)
	Table* openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields);

	// Alokuje objekt „int“
	static Object* Int(int value);
        // Alokuje objekt „double“
	static Object* Double(double value);
	// Alokuje objekt „string“
	static Object* String(std::string value);
	// Alokuje objekt „field“
	static FieldObject* Field(std::string name, FieldType type);

private:
	std::string dbName; //nazev databaze
	std::string *tables; //pole nazvu vytvorenych/nactenych tabulek
	int tablesTotal; //celkem mist v poli tabulek pro tabulky
	int createdTablesTotal; //celkem vytvorenuch/nactenych tabulek
	Db(std::string database); //konstruktor
	~Db();

	bool isTableCreatedOrLoaded(std::string table) const; //pomocnik pro zjisteni existence tabulky
	void addTableName(std::string table); //pridat nazev tabulky do seznamu nazvu
	bool tableSchemaFileExists(std::string table) const; //pomocnik pro zjisteni existence .dbsch
	bool tableDataFileExists(std::string table) const; //zjisteni existence .dbdat
	Table *loadTableSchemaFromFile(std::string name); //nacteni schemattu tabulky
	Table *loadTableDataFromFile(std::string name, Table *emptyTable); //nacteni dat
	void createDbDir() const; //vytvoreni slozky databaze, pokud jeste neexistuje
};
// --------------------------------------------------------

#endif

