#ifndef PIERNAIZQ_H_INCLUDED
#define PIERNAIZQ_H_INCLUDED

#include "objply.h"

class PiernaIzq {

private:
	ObjPLY* thigh = nullptr;
	ObjPLY* lowerleg = nullptr;
	ObjPLY* foot = nullptr;

	float PiernaInfX, PieX;

public:
	PiernaIzq();
	void draw(dibujado d, patron p);

	inline void rotarRodilla(float x) {
		PiernaInfX = x;
	}
	inline void rotarTalon(float x) {
		PieX = x;
	}
};

#endif