#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla2f& orientacion, GLenum idLuz)
{
	id = idLuz;
	posicion = Tupla4f(orientacion[0],orientacion[1],0,0);
}

void LuzDireccional::variarAnguloAlpha(float incremento)
{
	
}

void LuzDireccional::variarAnguloBeta(float incremento)
{
	
}