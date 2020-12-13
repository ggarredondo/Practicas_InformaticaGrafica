#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f& lposicion, GLenum idLuz, const Tupla4f& cdifuso, const Tupla4f& cespecular, const Tupla4f& cambiente)
{
	id = idLuz;
	posicion = Tupla4f(lposicion[0],lposicion[1],lposicion[2], 1);
	colorDifuso = cdifuso;
	colorEspecular = cespecular;
	colorAmbiente = cambiente;
}