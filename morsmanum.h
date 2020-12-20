#ifndef MORSMANUM_H_INCLUDED
#define MORSMANUM_H_INCLUDED

#include "objply.h"
#include "cabeza.h"
#include "brazoizq.h"
#include "brazodech.h"
#include "piernaizq.h"
#include "piernadech.h"

class Morsmanum {

private:
	ObjPLY* torso = nullptr;
	Cabeza* cabeza = nullptr;
	BrazoIzq* brazo_izq = nullptr;
	BrazoDech* brazo_dech = nullptr;
	PiernaIzq* pierna_izq = nullptr;
	PiernaDech* pierna_dech = nullptr;

	float cabezaX, cabezaY, cabezaZ,
		torsoX, torsoY, torsoZ,
		BrazoIzqX, BrazoIzqY, BrazoIzqZ,
		BrazoDechX, BrazoDechY, BrazoDechZ,
		PiernaIzqX, PiernaIzqY, PiernaIzqZ,
		PiernaDechX, PiernaDechY, PiernaDechZ;

public:
	Morsmanum();
	void draw(dibujado d, patron p);

	//Cabeza
	void rotarCabeza(float x, float y, float z);
	void abrirFauces(float apertura);

	//Torso
	void rotarTorso(float x, float y, float z);

	//BrazoIzq
	void rotarBrazoIzq(float x, float y, float z);

	//BrazoDech
	void rotarBrazoDech(float x, float y, float z);

	//PiernaIzq
	void rotarPiernaIzq(float x, float y, float z);

	//PiernaDech
	void rotarPiernaDech(float x, float y, float z);
};

#endif