#ifndef PIERNADECH_H_INCLUDED
#define PIERNADECH_H_INCLUDED

#include "objply.h"

class PiernaDech {

private:
	ObjPLY* thigh = nullptr;
	ObjPLY* lowerleg = nullptr;
	ObjPLY* foot = nullptr;

	float PiernaInfX, PieX;

public:
	PiernaDech();
	void draw(dibujado d, patron p);

	inline void rotarRodillaDech(float x) {
		PiernaInfX = x;
	}
	inline void rotarTalonDech(float x) {
		PieX = x;
	}
};

#endif