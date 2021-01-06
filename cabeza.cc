#include "cabeza.h"

Cabeza::Cabeza() 
{
	hair = new ObjPLY("./morsmanum/ply/hair.ply");
	hair->setTextura("./texturas/blackhair2.jpg");
	upperhead = new ObjPLY("./morsmanum/ply/upperhead.ply");
	upperhead->setTextura("./texturas/bark.jpg");
	lowerhead = new ObjPLY("./morsmanum/ply/lowerhead.ply");
	lowerhead->setTextura("./texturas/bark.jpg");
	fangs = new ObjPLY("./morsmanum/ply/fang.ply");
	tendon = new ObjPLY("./morsmanum/ply/tendon.ply");
	tendon->setTextura("./texturas/flesh2.jpg");

	ojo_izq = new Cilindro(2, 50, 1, 50, true);

	aperturaFauces = 0;
	cabezaSup = 0;
}

void Cabeza::draw(dibujado d, patron p)
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glScalef(2.1,3,2);
		glRotatef(70,0,1,0);
		glTranslatef(0.5,-3.5,-1);
		tendon->draw(d,p);
	glPopMatrix();

	glPushMatrix();
		glScalef(2,1.35,2);
		glRotatef(80,0,1,0);
		glTranslatef(-0.5,-1.4,0.4);
		fangs->draw(d,p);
	glPopMatrix();

	glPushMatrix();
		glScalef(2, 1.1, 2);
		lowerhead->draw(d, p);
	glPopMatrix();

	glPushMatrix();
		ojo_izq->draw(d,p);
	glPopMatrix();

	glPushMatrix();
		glScalef(2.1, 2.1, 2.1);
		glTranslatef(0, 9, 0);
		glTranslatef(0,aperturaFauces,0);
		glRotatef(aperturaFauces*3,1,0,-1);
		glRotatef(cabezaSup,1,0,1);
		upperhead->draw(d,p);
		hair->draw(d,p);
	glPopMatrix();
}