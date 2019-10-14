#ifndef _MONSTRUM_H
#define _MONSTRUM_H

#include "PohyblivyObjekt.h"
class Monstrum :
	public PohyblivyObjekt
{

private:
	int hp;
	int maxhp;
public:
	Monstrum(int id) : PohyblivyObjekt(id){};
	int GetHp() const;
	void SetHP(int hp) ;
	int GetMaxHP() const;
	void SetMaxHP(int maxhp) ;

};

#endif
