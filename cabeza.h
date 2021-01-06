#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "objply.h"
#include "cilindro.h"

class Cabeza {

private:
	ObjPLY* hair = nullptr;
	ObjPLY* upperhead = nullptr; 
	ObjPLY* lowerhead = nullptr;
	ObjPLY* tendon = nullptr;
	ObjPLY* fangs = nullptr;
	Cilindro* ojo_izq = nullptr;
	Cilindro* ojo_dech = nullptr;

	float aperturaFauces, cabezaSup;

public:
	Cabeza();
	void draw(dibujado d, patron p);

	inline void abrirFauces(float apertura) {
		aperturaFauces = apertura;
	}
	inline void inclinarCabezaSuperior(float inclinacion) {
		cabezaSup = inclinacion;
	}
};

#endif