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

public:
	BrazoIzq();
	void draw(dibujado d, patron p);
};

#endif