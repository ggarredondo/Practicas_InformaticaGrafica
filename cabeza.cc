#include "cabeza.h"

Cabeza::Cabeza() 
{
	hair = new ObjPLY("./morsmanum/ply/hair.ply");
	upperhead = new ObjPLY("./morsmanum/ply/upperhead.ply");
	lowerhead = new ObjPLY("./morsmanum/ply/lowerhead.ply");
}

void Cabeza::draw(dibujado d, patron p)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glScalef(2, 1.1, 2);
		lowerhead->draw(d, p);
	glPopMatrix();

	glPushMatrix();
		glScalef(2.1, 2.1, 2.1);
		glTranslatef(0, 9, 0);
		upperhead->draw(d,p);
		hair->draw(d,p);
	glPopMatrix();
}