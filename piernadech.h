#ifndef PIERNADECH_H_INCLUDED
#define PIERNADECH_H_INCLUDED

#include "objply.h"

class PiernaDech {

private:
	ObjPLY* thigh = nullptr;
	ObjPLY* lowerleg = nullptr;
	ObjPLY* foot = nullptr;

	float PiernaInfX, PiernaInfY, PiernaInfZ,
		PieX, PieY, PieZ;

public:
	PiernaDech();
	void draw(dibujado d, patron p);

	inline void rotarRodilla(float x, float y, float z) {
		PiernaInfX = x;
		PiernaInfY = y;
		PiernaInfZ = z;
	}
	inline void rotarTalon(float x, float y, float z) {
		PieX = x;
		PieY = y;
		PieZ = z;
	}
};

#endif