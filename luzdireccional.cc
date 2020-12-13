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

void LuzDireccional::rotacionEjeY() {
	posicion[0] = posicion[2]*sin(alpha) + posicion[0]*cos(alpha);
	posicion[2] = posicion[2]*cos(alpha) - posicion[0]*sin(alpha);
	alpha = 0;
}
	
void LuzDireccional::rotacionEjeX() {
	posicion[1] = posicion[1]*cos(beta) - posicion[2]*sin(beta);	
	posicion[2] = posicion[1]*sin(beta) + posicion[2]*cos(beta);
	beta = 0;
}

void LuzDireccional::activar()
{
	rotacionEjeY();
	rotacionEjeX();
	Luz::activar();
}