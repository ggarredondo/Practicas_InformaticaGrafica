#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz 
{
protected:
	Tupla4f posicion, colorDifuso, colorEspecular, colorAmbiente;
	GLenum id;

public:
	void activar();
	inline void desactivar() {
		glDisable(id);
	}
};

#endif