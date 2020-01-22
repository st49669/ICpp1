#ifndef __OBJECT_H
#define __OBJECT_H

#include "stdafx.h"
#include "platform.h"

#include <iostream>

// Typ datov�ho pole
enum struct FieldType {
	String,
	Double,
	Integer,
	Field
};

// Polymorfn� datov� objekt (reprezentuje jednu datovou hodnotu v tabulce)
// Rozhran� vyhovuje z�kladn�m typ�m int, double, string; pro typ �field� je rozhran� roz���eno
class DLL_SPEC Object {
public:
	Object() {};
	virtual ~Object() {};

	// Gettery a settery podle typu
	// Jejich funkce je definov�na jen v p��pad�, �e aktu�ln� objekt je odpov�daj�c�ho typu
	// Automatick� konverze v z�kladn�m API nejsou vy�adov�ny

	virtual std::string getString() const { return ""; };
	virtual void setString(std::string value) {};

	virtual int getInt() const { return 0; };
	virtual void setInt(int value) {};

	virtual double getDouble() const { return 0.0; };
	virtual void setDouble(double value) {};

	// Vrac� true, pokud aktu�ln� objekt p�edstavuje dan� typ
	virtual bool isType(FieldType type) const = 0;
};

#endif
