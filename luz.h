#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz 
{
private:
	Tupla4f posicion, colorAmbiente, colorDifuso, colorEspecular;
	GLenum id;

public:
	void activar();
};

#endif