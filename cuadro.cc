#include "cuadro.h"

Cuadro::Cuadro()
{
	cubo = new Cubo(100);
	std::vector<Tupla2f> ct = { {1,1},
								{0,1},
								{1,0},
								{0,0} };
	cubo->setTextura("./texturas/grass.jpg",ct);
	cubo->setMaterial(Material(Tupla4f(0.7,0.7,0.7,0.7),Tupla4f(0,0,0,0),Tupla4f(0.2,0.2,0.2,0.2),1));
}

void Cuadro::draw(dibujado d, patron p)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(0,-110,0);
		glRotatef(-90,1,0,0);
		glScalef(30,30,0);
		cubo->draw(d,p);
	glPopMatrix();
}