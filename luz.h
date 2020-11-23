#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz 
{
protected:
	Tupla4f posicion, colorAmbiente, colorDifuso, colorEspecular;
	GLenum id;

public:
	void activar();
};

#endif