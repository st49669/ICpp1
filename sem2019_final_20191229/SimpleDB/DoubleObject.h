#ifndef __DOUBLEOBJECT_H
#define __DOUBLEOBJECT_H
#include "Object.h"
class DLL_SPEC DoubleObject : public Object {
private:
	double value;
public:
	DoubleObject() : value(0.0) {}
	DoubleObject(double v) : value(v) {}
	virtual double getDouble() const override { return value; }
	virtual void setDouble(double value) override { this->value = value; }
	virtual bool isType(FieldType type) const override { return (type == FieldType::Double); }
};

#endif