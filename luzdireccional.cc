#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla3f& orientacion, GLenum idLuz, const Tupla4f& cdifuso, const Tupla4f& cespecular, const Tupla4f& cambiente)
{
	id = idLuz;
	posicion = Tupla4f(orientacion[0],orientacion[1],orientacion[2],0); //posiblemente mal
	colorDifuso = cdifuso;
	colorEspecular = cespecular;
	colorAmbiente = cambiente;
}

void LuzDireccional::variarAnguloAlpha(float incremento)
{
	glPushMatrix();
		glRotatef(incremento, 0, 1, 0);
	glPopMatrix();
}

void LuzDireccional::variarAnguloBeta(float incremento)
{
	glPushMatrix();
		glRotatef(incremento, -1, 0, 0);
	glPopMatrix();
}