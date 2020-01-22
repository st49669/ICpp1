#ifndef __STRINGOBJECT_H
#define __STRINGOBJECT_H
#include "Object.h"
class DLL_SPEC StringObject : public Object {
private:
	std::string value;
public:
	StringObject() : value("") {}
	StringObject(std::string v) : value(v) {}
	virtual std::string getString() const override { return value; }
	virtual void setString(std::string value) override { this->value = value; }
	virtual bool isType(FieldType type) const override { return (type == FieldType::String); }
};
#endif