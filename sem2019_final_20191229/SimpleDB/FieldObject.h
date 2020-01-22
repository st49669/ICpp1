#ifndef __FIELDOBJECT_H
#define __FIELDOBJECT_H
#include "Object.h"
class DLL_SPEC FieldObject : public Object {
private:
	std::string name;
	FieldType type;
public:
	FieldObject() {}
	FieldObject(std::string name, FieldType type) :name(name), type(type) {}

	// N�zev sloupe�ku
	std::string getName() const { return name; }
	// Typ sloupe�ku
	FieldType getType() const { return type; }

	virtual bool isType(FieldType type) const override { return (type == FieldType::Field); }
};

#endif