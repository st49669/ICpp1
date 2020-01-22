#ifndef __INTOBJECT_H
#define __INTOBJECT_H
#include "Object.h"
class DLL_SPEC IntObject : public Object {
private:
	int value;
public:
	IntObject() : value(0) {}
	IntObject(int v) : value(v) {}
	virtual int getInt() const override { return value; }
	virtual void setInt(int value) override { this->value = value; }
	virtual bool isType(FieldType type) const override { return (type == FieldType::Integer); }
};

#endif