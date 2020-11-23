#include "luz.h"

void Luz::activar() 
{
	glEnable(id);
	glLightfv(id, GL_POSITION, posicion);
}