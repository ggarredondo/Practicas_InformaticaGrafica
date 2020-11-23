#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f& lposicion, GLenum idLuz)
{
	id = idLuz;
	posicion = Tupla4f(lposicion[0],lposicion[1],lposicion[2],0);
	colorAmbiente = Tupla4f(0, 0, 0, 1);
	colorDifuso = Tupla4f(1, 1, 1, 1);
	colorEspecular = Tupla4f(1, 1, 1, 1);
}