#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "objply.h"

class Cabeza {

private:
	ObjPLY* hair = nullptr;
	ObjPLY* upperhead = nullptr; 
	ObjPLY* left_tendon = nullptr;
	ObjPLY* right_tendon = nullptr;
	ObjPLY* lowerhead = nullptr;

public:
	Cabeza();
	void draw(dibujado d, patron p);
};

#endif