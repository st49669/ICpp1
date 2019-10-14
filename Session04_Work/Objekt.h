#ifndef _OBJEKT_H
#define _OBJEKT_H
class Objekt
{
private:
	int id;
	double x;
	double y;

public:
	Objekt(int id);
	virtual ~Objekt() {};
	double getX()const;
	double getY()const;
	void setX(double  x) ;
	void setY(double  y) ;
	double getID()const;
};
#endif
