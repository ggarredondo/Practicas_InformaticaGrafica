#ifndef PIERNADECH_H_INCLUDED
#define PIERNADECH_H_INCLUDED

#include "objply.h"

class PiernaDech {

private:
	ObjPLY* thigh = nullptr;
	ObjPLY* lowerleg = nullptr;
	ObjPLY* foot = nullptr;

public:
	PiernaDech();
	void draw(dibujado d, patron p);
};

#endif