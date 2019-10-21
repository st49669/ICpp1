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
	double GetX()const;
	double GetY()const;
	void SetX(double  x) ;
	void SetY(double  y) ;
	double GetID()const;
};
#endif
