#ifndef MORSMANUM_H_INCLUDED
#define MORSMANUM_H_INCLUDED

#include "objply.h"
#include "cabeza.h"
#include "brazoizq.h"
#include "piernaizq.h"

class Morsmanum {

private:
	ObjPLY* torso = nullptr;
	Cabeza* cabeza = nullptr;
	BrazoIzq* brazo_izq = nullptr;
	//BrazoDech* brazo_dech = nullptr;
	PiernaIzq* pierna_izq = nullptr;
	//PiernaDech* pierna_dech = nullptr;

public:
	Morsmanum();
	void draw(dibujado d, patron p);
};

#endif