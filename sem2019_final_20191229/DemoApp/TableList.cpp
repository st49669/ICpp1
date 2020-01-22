#include "stdafx.h"
#include "TableList.h"


TableList::~TableList() {
	while (_first != nullptr) {
		LinkedList *prev = _first;
		_first = _first->next;
		delete prev;
	}
}

void TableList::add(std::string name, Table *table){
	LinkedList *temp = new LinkedList(name, table);
	if (_first == nullptr) { //pridani 1. prvku
		_first = temp;
	}
	else {
		LinkedList* temp2 = _first; //prohledavani od zacatku
		while (temp2->next != nullptr) { //neznam aktualini pozici v seznamu, musim se tam dostat
			temp2 = temp2->next;
		}
		temp2->next = temp;
	}
}

Table *TableList::getTableByName(std::string name) {
	LinkedList *curr = _first;
	while (curr != nullptr) {
		if (curr->name.compare(name) == 0) {
			return curr->table;
		}
		curr = curr->next;
	}
	return nullptr;
}

void TableList::printTableList() {
	LinkedList *curr = _first;
	while (curr != nullptr) {
		std::cout << "\t" << curr->name.c_str() << std::endl;
		curr = curr->next;
	}
}

void TableList::commitAll() {
	LinkedList *curr = _first;
	while (curr != nullptr) {
		curr->table->commit();
		curr = curr->next;
	}
}

void TableList::closeAll() {
	LinkedList *curr = _first;
	while (curr != nullptr) {
		curr->table->close();
		curr = curr->next;
	}
}
