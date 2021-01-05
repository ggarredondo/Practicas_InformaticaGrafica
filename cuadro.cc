#include "cuadro.h"

Cuadro::Cuadro()
{
	cubo = new Cubo(100);
	std::vector<Tupla2f> ct = { {1,1},
								{0,1},
								{1,0},
								{0,0} };
	cubo->setTextura("./texturas/minecraft.jpg",ct);
}

void Cuadro::draw(dibujado d, patron p)
{
	glPushMatrix();
		glTranslatef(-100,0,0);
		glScalef(1,1,0.1);
		cubo->draw(d,p);
	glPopMatrix();
}