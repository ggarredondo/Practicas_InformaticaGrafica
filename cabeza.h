#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "objply.h"

class Cabeza {

private:
	ObjPLY* hair = nullptr;
	ObjPLY* upperhead = nullptr; 
	ObjPLY* tendons = nullptr;
	ObjPLY* lowerhead = nullptr;

public:
	Cabeza();
	void draw(dibujado d, patron p);
};

#endif