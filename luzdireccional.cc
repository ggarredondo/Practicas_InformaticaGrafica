#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla2f& orientacion, GLenum idLuz, const Tupla4f& cdifuso, const Tupla4f& cespecular, const Tupla4f& cambiente)
{
	id = idLuz;
	posicion = Tupla4f(0,0,1,0);
	colorDifuso = cdifuso;
	colorEspecular = cespecular;
	colorAmbiente = cambiente;
	alpha = orientacion[0];
	beta = orientacion[1];
}

void LuzDireccional::activar()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glRotatef(alpha, 0, 1, 0);
		glRotatef(beta, -1, 0, 0);
		Luz::activar();
	glPopMatrix();
}