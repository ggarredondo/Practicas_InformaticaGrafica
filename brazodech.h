#ifndef BRAZODECH_H_INCLUDED
#define BRAZODECH_H_INCLUDED

#include "objply.h"

class BrazoDech {

private:
	ObjPLY* shoulder = nullptr;
	ObjPLY* forearm = nullptr;
	ObjPLY* hand = nullptr;
	ObjPLY* fingers = nullptr;
	ObjPLY* thumb = nullptr;

public:
	BrazoDech();
	void draw(dibujado d, patron p);
};

#endif