#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "objply.h"

class Cabeza {

private:
	ObjPLY* hair = nullptr;
	ObjPLY* upperhead = nullptr; 
	ObjPLY* lowerhead = nullptr;
	ObjPLY* tendon = nullptr;
	ObjPLY* fangs = nullptr;

	float aperturaFauces;

public:
	Cabeza();
	void draw(dibujado d, patron p);

	inline void abrirFauces(float apertura) {
		aperturaFauces = apertura;
	}
};

#endif