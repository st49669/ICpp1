#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "TableList.h"


using namespace std;

//pro usnadneni vypisu hlavniho menu
struct Main_Menu{
	char choice; //znak volby, pouzivam cisla
	char const *text; //text volby
};

//Vypis tabulky s cislem radku, pomoci iterattoru
void printTableContentByIteration(Table *t) {
	cout << "\n\t============\n\tObsah tabulky\n\t============\n\n";
	size_t fieldsCount = t->getFieldCount();
	auto fields = t->getFields();
	cout << "#radek";
	for (size_t i = 0; i < fieldsCount; ++i) {
		cout << "\t" << fields[i]->getName();
	}
	cout << endl;
	Iterator *it = t->select();
	int radek = 0;
	while (it->moveNext()) {
		cout << radek;
		auto row = it->getRow();
		for (size_t i = 0; i < fieldsCount; ++i) {
			switch (fields[i]->getType()) {
				case FieldType::Integer:
					cout << "\t" << row[i]->getInt();
					break;
				case FieldType::Double:
					cout << "\t" << row[i]->getDouble();
					break;
				case FieldType::String:
					cout << "\t" << row[i]->getString();
					break;
				default: break;	
			}	
		}
		cout << endl;
		++radek;
	}
	it->close();
	cout << endl;
}

//ziskani konkretniho radku tabulky s vyuzitim itteratoru
Object **getTableRowByRowNum(Table *t, int rowNum) {
	Iterator *it = t->select();
	while (it->moveNext()) {
		auto row = it->getRow();
		if (rowNum == it->getRowId()) {
			it->close(); //pozor na zavirani iteratoru
			return row;
		}
	}
	it->close();
	return nullptr;
}

//pomocny vypis pri vytvareni radku tabulky
void printColumnType(FieldType type) {
	switch (type) {
	case FieldType::Integer:
		cout << "\t Typ: celociselna hodnota" << endl;
		break;
	case FieldType::Double:
		cout << "\t Typ: realne cislo" << endl;
		break;
	case FieldType::String:
		cout << "\t Typ: retezec" << endl;
		break;
	default: break;
	}
}

//primitivni vypis tabulek
void printTables(TableList *tables) {
	cout << "\n\t============\n\tSeznam tabulek\n\t============\n\n";
	tables->printTableList();
	cout << endl;
}

//menu - vypis obsahu tabulky
void printTableContent(TableList *tables) { 
	cout << "\n\n";
	tables->printTableList();
	cout << "\nZadej nazev tabulky: ";
	string input;
	getline(cin, input);
	Table *t = tables->getTableByName(input);
	if (t != nullptr) printTableContentByIteration(t);
	else cout << "Neplatny nazev tabulky, navrat do menu..." << endl;
}

//validace datoveho typu, pro Int a pripadne Double
bool validateValueByType(string val, FieldType type) {
	std::istringstream iss(val);
	switch (type) {
	case FieldType::Integer:
		int num;
		iss >> num;
		if (iss.fail()) {
			return false;
		}
		break;
	case FieldType::Double:
		double dou;
		iss >> dou;
		if (iss.fail()) {
			return false;
		}
		break;
	default: break;
	}
	return true;
}

//konverze sttring na int
int convertStringToInt(string val) { //volani musi predchazet kontrola!!!
	std::istringstream iss(val);
	int num;
	iss >> num;
	return num;
}

//konverze string na double
double convertStringToDouble(string val) { //volani musi predchazet kontrola!!!
	std::istringstream iss(val);
	double num;
	iss >> num;
	return num;
}

//alokace objektu pri vytvareni raku
Object *allocDbObjByType(string val, FieldType type) {
	switch (type) {
	case FieldType::Integer:
		return Db::Int(convertStringToInt(val));
	case FieldType::Double:
		return Db::Double(convertStringToDouble(val));
	default: break;
	}
	return Db::String(val);
}

//pomocnik pro vlozeni radku do tabulky, aby byl vytvoren spravny objekt radku
void insertTableRow(string *inputs, int colsCount, Table *t) {
	Object **row;
	Object **values = new Object*[colsCount];
	auto fields = t->getFields();
	switch (colsCount) {
		case 2:
			values[0] = allocDbObjByType(inputs[0], fields[0]->getType());
			values[1] = allocDbObjByType(inputs[1], fields[1]->getType());
			row = combineToRow(values[0], values[1]);
			break;
		case 3:
			values[0] = allocDbObjByType(inputs[0], fields[0]->getType());
			values[1] = allocDbObjByType(inputs[1], fields[1]->getType());
			values[2] = allocDbObjByType(inputs[2], fields[2]->getType());
			row = combineToRow(values[0], values[1], values[2]);
			break;
		case 4:
			values[0] = allocDbObjByType(inputs[0], fields[0]->getType());
			values[1] = allocDbObjByType(inputs[1], fields[1]->getType());
			values[2] = allocDbObjByType(inputs[2], fields[2]->getType());
			values[3] = allocDbObjByType(inputs[3], fields[3]->getType());
			row = combineToRow(values[0], values[1], values[2], values[3]);
			break;
		case 5:
			values[0] = allocDbObjByType(inputs[0], fields[0]->getType());
			values[1] = allocDbObjByType(inputs[1], fields[1]->getType());
			values[2] = allocDbObjByType(inputs[2], fields[2]->getType());
			values[3] = allocDbObjByType(inputs[3], fields[3]->getType());
			values[4] = allocDbObjByType(inputs[4], fields[4]->getType());
			row = combineToRow(values[0], values[1], values[2], values[3], values[4]);
			break;
		default: //pravdepodobne zbytecny
			cout << "Radek nebyl vlozen, pocet sloupecku musi byt 2, 3, 4 nebo 5..." << endl;
			return;
	}
	t->insert(row);
}

//zjisteni, zda tabulka v 1. sloupci obsahuje hodnotu
bool tableContainsId(Table *t, int id) {
	Iterator *it = t->select();
	while (it->moveNext()) {
		auto row = it->getRow();
		if (row[0]->getInt() == id) {
			it->close();
			return true;
		}
	}
	it->close();
	return false;
}

//menu - vytvoreni radku tabulky
void createTableRow(TableList *tables) {
	cout << "\n\n";
	tables->printTableList();
	cout << "\nZadej nazev tabulky: ";
	string input;
	getline(cin, input);
	Table *t = tables->getTableByName(input);
	bool autoIncrement = (input.compare("osoby") == 0); //automaticky vytvaret ID osoby
	bool constraint = (input.compare("kontakty") == 0); //zamezit vlozeni neexistujiciho ID osoby
	if (t != nullptr) {
		int fieldsCount = t->getFieldCount();
		string *inputs = new string[fieldsCount];
		auto fields = t->getFields();
		for (size_t i = (autoIncrement ? 1 : 0); i < fieldsCount; ++i) {
			cout << "\nSloupec: " << fields[i]->getName();
			printColumnType(fields[i]->getType());
			cout << "Zadej platnou hodnotu dle sloupce: ";
			getline(cin, inputs[i]);
			if (!validateValueByType(inputs[i], fields[i]->getType())) {
				cout << "\nZadana neplatna hodnota, navrat do menu..." << endl;
				delete[] inputs;
				return; //nutno zabranit pokracovyni pri neplattne hodnote...
			}
			//overeni existence osoby
			if (i == 0 && constraint && !tableContainsId(tables->getTableByName("osoby"), convertStringToInt(inputs[0]))) {
				cout << "\nZadane ID neodpovida existujicim ID osob..." << endl;
				delete[] inputs;
				return; //nutno zabranit pokracovani pri neplatnem ID
			}
		}
		if (autoIncrement) { //dosadit spravnou hodnotu autoIncrementu do tabulky osoby
			Iterator *it = t->select();
			int highestId = -1;
			while (it->moveNext()) {
				auto row = it->getRow();
				int currId = row[0]->getInt();
				if (currId > highestId) highestId = currId;
			}
			it->close();
			++highestId; //posunout na nasledujici hodnotu po nejvyssi nalezene
			inputs[0] = to_string(highestId); //pridat cislo mezi retezce
		}
		insertTableRow(inputs, fieldsCount, t);
		delete[] inputs;
		printTableContentByIteration(t);
	}
	else cout << "Neplatny nazev tabulky, navrat do menu..." << endl;
}

//menu - uprava radku tabulky
void updateTableRow(TableList *tables) {
	cout << "\n\n";
	tables->printTableList();
	cout << "\nZadej nazev tabulky: ";
	string input;
	getline(cin, input);
	//zamezeni upravy 1. sloupce (id) v osoback a kontaktech:
	bool skipFirstCol = ((input.compare("osoby") == 0) || (input.compare("kontakty") == 0));
	Table *t = tables->getTableByName(input);
	if (t != nullptr) {
		int rowsTotal = t->getRowCount();
		printTableContentByIteration(t);
		cout << "\nZadej #radek k uprave: ";
		getline(cin, input);
		if (!validateValueByType(input, FieldType::Integer)) {
			cout << "\nZadan neplatny #radek." << endl;
			return;
		}
		int rowId = convertStringToInt(input);
		if (rowId < 0 || rowId >= rowsTotal) {
			cout << "\nZadan #radek < 0 nebo neexistujici." << endl;
			return;
		}
		cout << "Upravuji radek #" << rowId << endl;
		auto row = getTableRowByRowNum(t, rowId);
		auto fields = t->getFields();
		int colCount = t->getFieldCount();
		for (size_t i = (skipFirstCol ? 1 : 0); i < colCount; ++i) {
			switch (fields[i]->getType()) {
				case FieldType::Integer:
					cout << "Zadej celociselnou hodnotu sloupce \"" << fields[i]->getName() << "\": ";
					getline(cin, input);
					if (validateValueByType(input, FieldType::Integer)) {
						row[i]->setInt(convertStringToInt(input));
					} else {
						cout << "Zadana hodnota sloupce \"" << fields[i]->getName() << "\" neni celociselna." << endl;
						return;
					}
					break;
				case FieldType::Double:
					cout << "Zadej realne cislo pro hodnotu sloupce \"" << fields[i]->getName() << "\": ";
					getline(cin, input);
					if (validateValueByType(input, FieldType::Double)) {
						row[i]->setDouble(convertStringToDouble(input));
					} else {
						cout << "Zadana hodnota sloupce \"" << fields[i]->getName() << "\" neni realne cislo." << endl;
						return;
					}
					break;
				default: //string
					cout << "Zadej hodnotu sloupce \"" << fields[i]->getName() << "\": ";
					getline(cin, input);
					row[i]->setString(input);
					break;
			}
		}
		printTableContentByIteration(t);
	}
	else cout << "Neplatny nazev tabulky, navrat do menu..." << endl;
}

//menu - vymazani radku tatbulky
void deleteTableRow(TableList *tables) {
	cout << "\n\n";
	tables->printTableList();
	cout << "\nZadej nazev tabulky: ";
	string input;
	getline(cin, input);
	bool preventCascDel = (input.compare("osoby") == 0); //kontrolovat, jestli odstranena osoba nema existujici kontakty
	Table *t = tables->getTableByName(input);
	if (t != nullptr) {
		int rowsTotal = t->getRowCount();
		printTableContentByIteration(t);
		cout << "\nZadej #radek k vymazani: ";
		getline(cin, input);
		if (!validateValueByType(input, FieldType::Integer)) {
			cout << "\nZadan neplatny #radek." << endl;
			return;
		}
		int rowId = convertStringToInt(input);
		if (rowId < 0 || rowId >= rowsTotal) {
			cout << "\nZadan #radek < 0 nebo neexistujici." << endl;
			return;
		}
		if (preventCascDel) { //nemazat osobu, ke kttere existuje kontakt
			auto row = getTableRowByRowNum(t, rowId);
			if (tableContainsId(tables->getTableByName("kontakty") , row[0]->getInt())) {
				cout << "\nOsobu nelze vymazat, protoze ma prirazeny alespon 1 kontakt." << endl;
				return;
			}
		}
		t->remove(rowId);
		printTableContentByIteration(t);
	}
}

//menu - vytvoreni nove tabulky
void createTable(TableList *tables, Db *db) {
	cout << "\n\n";
	cout << "\nZadej nazev tabulky k vytvoreni: ";
	string name;
	getline(cin, name);
	if (!name.empty()) {
		string colsStr;
		cout << "\nZadej pocet sloupcu k vytvoreni o poctu 2, 3, 4 nebo 5: ";
		getline(cin, colsStr);
		if (!validateValueByType(colsStr, FieldType::Integer)) {
			cout << "\nZadan neplatny pocet sloupcu." << endl;
			return;
		}
		int cols = convertStringToInt(colsStr);
		if (cols < 2 || cols > 5) {
			cout << "\nPocet radku musi byt z intervalu <2, 5>." << endl;
			return;
		}
		FieldObject **fieldsObjsToCreate = new FieldObject *[cols];
		for (size_t i = 0; i < cols; i++) {
			bool success = false;
			string type, colName;
			while (!success) { //nedovolit vytvoreni sloupce ben nazvu
				cout << "\nZadej nazev sloupce c. " << (i + 1) << ": ";
				getline(cin, colName);
				if (colName.empty()) {
					cout << "\nNazev sloupce nesmi byt prazdny." << endl;
				}
				else success = true;
			}
			cout << "\nDatove typy:\n1 - cele cislo\n2 - realne cislo\njinak retezec...\n" << endl;
			cout << "Zadej datovy typ sloupce c. " << (i + 1) << ": ";
			getline(cin, type);
			type = type[0]; //pouze 1. znak rozhoduje
			if (type.compare("1") == 0) {
				fieldsObjsToCreate[i] = new FieldObject(colName, FieldType::Integer);
			}
			else if (type.compare("2") == 0) {
				fieldsObjsToCreate[i] = new FieldObject(colName, FieldType::Double);
			}
			else {
				fieldsObjsToCreate[i] = new FieldObject(colName, FieldType::String);
			}
		} //end for (size_t i = 0; i < cols; i++)
		Table *t = db->openOrCreateTable(name, cols, fieldsObjsToCreate);
		tables->add(name, t);
		printTableContentByIteration(t);
	} else cout << "Nazev nove tabulky nemuze byt prazdny..." << endl;
}

//menu - ulozit praci a ukoncit program
void saveAndQuit(TableList *tables, Db *db) {
	tables->commitAll();
	tables->closeAll();
	delete tables;
	db->close();
}

static const Main_Menu main_menu[] = {
	{ '1', "1 - Seznam tabulek" },
	{ '2', "2 - Obsah tabulky" },
	{ '3', "3 - Vytvoreni radku tabulky" },
	{ '4', "4 - Uprava radku tabulky" },
	{ '5', "5 - Smazani radku tabulky" },
	{ '6', "6 - Vytvoreni nove tabulky" },
	{ '9', "9 - O programu" },
	{ '0', "0 - Ulozit a ukoncit" },
}; //pole struktur se znakem volby, tetxem volby a nazvem procedury

static const size_t menuOptionsCount =
sizeof(main_menu) / sizeof(main_menu[0]); //pocet prvku v poli struktur Main_Menu

//menu - o programu
void printAbout() {
	cout << "\n\t============\n\tO programu\n\t============\n\n";
	cout << "Autor: Petr Nosek, st49669\n" << endl;
	cout << "Program obsahuje databazi zamestnancu, kontaktu na ne," << endl;
	cout << "a tabulku s parametry pracovnich pozic." << endl;
	cout << "Jsou umozneny zakladni CRUD operace dle zadani." << endl;
	cout << "Tabulka zamestnancu a kontaktu je spojena relaci 1:N.\n" << endl;
	cout << "V praxi to znamena nasledujici:" << endl;
	cout << "Pri vytvareni osoby je jeji ID nastaveno automaticky na nejvyssi nasledujici." << endl;
	cout << "Pri vytvareni kontaktu nelze pouzit neexistujici ID osoby." << endl;
	cout << "Pri uprave osob nebo kontaktu nelze menit zadane ID osoby." << endl;
	cout << "Pri mazani osob nelze vymazat takovou, ktera ma prirazeny alespon 1 kontakt.\n" << endl;
	cout << "Ukladani probiha do adresare dle nazvu databaze," << endl;
	cout << "umistenem v adresari \"databases\" v korenu projektu.\n" << endl;
	cout << "Program umi vytvorit novou tabulku, ale dokaze ji po opetovnem spusteni nacist" << endl;
	cout << "pouze po pripsani jejiho nazvu do tablesToLoad[] v metode main()." << endl;
	cout << "\n\t============\n\n";
}

//vypis hl. menu a rozhodovaci logika hl. menu
bool mainMenuLoop(TableList *tables, Db *db) {
	cout << "\n\t============\n\tHlavni menu\n\t============\n\n";
	for (size_t i = 0; i < menuOptionsCount; ++i) { //Vypis hlavniho menu
		cout << main_menu[i].text << endl;;
	}
	cout << "\nZadej volbu: ";
	string input;
	getline(cin, input);
	char choice = input[0];
	switch (choice) {
		case '1': //1 - Seznam tabulek
			printTables(tables);
			break;
		case '2': //2 - Obsah tabulky
			printTableContent(tables);
			break;
		case '3': //3 - Vytvoreni radku tabulky
			createTableRow(tables);
			break;
		case '4': //4 - Uprava radku tabulky
			updateTableRow(tables);
			break;
		case '5': //5 - Smazani radku tabulky
			deleteTableRow(tables);
			break;
		case '6': //6 - Vytvoreni nove tabulky
			createTable(tables, db);
			break;
		case '9': //9 - O programu
			printAbout();
			break;
		case '0': //0 - Ulozit a ukoncit
			saveAndQuit(tables, db);
			return false;
		default: break;
	}
	return true;
}


int main() {
	Db* db = Db::open("zamestnanci"); //nazev databaze a adresare s ni
	const string tablesToLoad[] = {"osoby","kontakty","pozice"}; //nazvy tabulek v datatbazi
	const size_t tablesCount = sizeof(tablesToLoad) / sizeof(tablesToLoad[0]); //pocet tabulek
	TableList *tables = new TableList(); //ADS singly linked list
	for (size_t i = 0; i < tablesCount; ++i) {
		tables->add(tablesToLoad[i], db->openTable(tablesToLoad[i])); //nacteni tabulek
	}
	try {
		bool loop = true;
		while (loop) {
			loop = mainMenuLoop(tables,db);
			system("pause");
		}
	} catch (const invalid_argument &e) {
		cerr << e.what() << endl;
	} catch (const logic_error &e) {
		cerr << e.what() << endl;
	} 
	return 0;
}