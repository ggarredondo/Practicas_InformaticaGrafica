#ifndef PIERNAIZQ_H_INCLUDED
#define PIERNAIZQ_H_INCLUDED

#include "objply.h"

class PiernaIzq {

private:
	ObjPLY* thigh = nullptr;
	ObjPLY* lowerleg = nullptr;
	ObjPLY* foot = nullptr;

public:
	PiernaIzq();
	void draw(dibujado d, patron p);
};

#endif