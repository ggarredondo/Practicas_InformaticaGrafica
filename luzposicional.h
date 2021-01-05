#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz
{
public:
	LuzPosicional(const Tupla3f& lposicion, GLenum idLuz, const Tupla4f& cdifuso, const Tupla4f& cespecular, const Tupla4f& cambiente);
	inline void trasladarLuz(float x, float y, float z) {
		posicion = {x,y,z,1};
	}
};

#endif