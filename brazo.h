#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "objply.h"

class Brazo {

private:
	ObjPLY* shoulder = nullptr;
	ObjPLY* forearm = nullptr;
	ObjPLY* hand = nullptr;
	ObjPLY* fingers = nullptr;
	ObjPLY* thumb = nullptr;

public:
	Brazo();
	void draw(dibujado d, patron p);
};

#endif