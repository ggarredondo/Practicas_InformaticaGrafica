#include "cabeza.h"

Cabeza::Cabeza() 
{
	hair = new ObjPLY("./morsmanum/ply/hair.ply");
	hair->setMaterial(Material({0.01,0.01,0.01,1},{0.01,0.01,0.01,1},{0,0,0,0},1));

	upperhead = new ObjPLY("./morsmanum/ply/upperhead.ply");
	upperhead->setMaterial(Material({0.34,0.25,0.18,1},{0,0,0,0},{0,0,0,0},1));

	lowerhead = new ObjPLY("./morsmanum/ply/lowerhead.ply");
	lowerhead->setMaterial(Material({0.34,0.25,0.18,1},{0,0,0,0},{0,0,0,0},1));

	fangs = new ObjPLY("./morsmanum/ply/fang.ply");
	fangs->setMaterial(Material({1,1,1,1},{0,0,0,0},{0,0,0,0},1));

	tendon = new ObjPLY("./morsmanum/ply/tendon.ply");
	tendon->setMaterial(Material({1,0.5,0.5,1},{0,0,0,1},{0,0,0,0},1));

	aperturaFauces = 0;
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
		glScalef(2.1, 2.1, 2.1);
		glTranslatef(0, 9, 0);
		glTranslatef(0,aperturaFauces,0);
		glRotatef(aperturaFauces*3,1,0,-1);
		upperhead->draw(d,p);
		hair->draw(d,p);
	glPopMatrix();
}