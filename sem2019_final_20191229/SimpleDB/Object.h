#ifndef __OBJECT_H
#define __OBJECT_H

#include "stdafx.h"
#include "platform.h"

#include <iostream>

// Typ datového pole
enum struct FieldType {
	String,
	Double,
	Integer,
	Field
};

// Polymorfní datový objekt (reprezentuje jednu datovou hodnotu v tabulce)
// Rozhraní vyhovuje základním typùm int, double, string; pro typ „field“ je rozhraní rozšíøeno
class DLL_SPEC Object {
public:
	Object() {};
	virtual ~Object() {};

	// Gettery a settery podle typu
	// Jejich funkce je definována jen v pøípadì, že aktuální objekt je odpovídajícího typu
	// Automatické konverze v základním API nejsou vyžadovány

	virtual std::string getString() const { return ""; };
	virtual void setString(std::string value) {};

	virtual int getInt() const { return 0; };
	virtual void setInt(int value) {};

	virtual double getDouble() const { return 0.0; };
	virtual void setDouble(double value) {};

	// Vrací true, pokud aktuální objekt pøedstavuje daný typ
	virtual bool isType(FieldType type) const = 0;
};

#endif
