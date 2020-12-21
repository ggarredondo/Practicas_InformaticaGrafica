#ifndef BRAZOIZQ_H_INCLUDED
#define BRAZOIZQ_H_INCLUDED

#include "objply.h"

class BrazoIzq {

private:
	ObjPLY* shoulder = nullptr;
	ObjPLY* forearm = nullptr;
	ObjPLY* hand = nullptr;
	ObjPLY* fingers = nullptr;
	ObjPLY* thumb = nullptr;

	float AntebrazoY, ManoY, ManoZ, DedosZ, PulgarY, PulgarZ;

public:
	BrazoIzq();
	void draw(dibujado d, patron p);

	inline void rotarAntebrazo(float y) {
		AntebrazoY = y;
	}
	inline void rotarMano(float y, float z) {
		ManoY = y;
		ManoZ = z;
	}
	inline void rotarDedos(float z) {
		DedosZ = z;
	}
	inline void rotarPulgar(float y, float z) {
		PulgarY = y;
		PulgarZ = z;
	}
};

#endif