#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "cubo.h"

class Cuadro
{
private:
	Cubo* cubo;

public:
	Cuadro();
	void draw(dibujado d, patron p);
};

#endif