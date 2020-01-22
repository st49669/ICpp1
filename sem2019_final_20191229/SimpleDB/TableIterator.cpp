#include "stdafx.h"
#include "TableIterator.h"


TableIterator::TableIterator(Object ***data, int dataRowsTotal) {
	this->data = data;
	this->dataRowsTotal = dataRowsTotal;
	iterPos = 0;
}

TableIterator::~TableIterator() {
	data = nullptr;
}

bool TableIterator::moveNext() {
	return (iterPos != dataRowsTotal);
}

Object **TableIterator::getRow() {
	++iterPos;
	return data[iterPos-1];
}

int TableIterator::getRowId() {
	return iterPos-1; //iterPos predstavuje index budouciho radku
}

void TableIterator::close() {
	TableIterator::~TableIterator();
}
