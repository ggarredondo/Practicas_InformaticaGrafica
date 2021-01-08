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
	fangs->setMaterial(Material(Tupla4f(1,1,1,1),Tupla4f(1,1,1,1),Tupla4f(0,0,0,0), 1));
	tendon = new ObjPLY("./morsmanum/ply/tendon.ply");
	tendon->setTextura("./texturas/flesh2.jpg");

	ojo_izq = new Ojo(false);
	ojo_dech = new Ojo(true);

	aperturaFauces = 0;
	cabezaSup = 0;
}

Ojo::Ojo(bool derecho) {
	cil = new Cilindro(2, 50, 0, 4, true);
	dech = derecho;
}

void Ojo::draw(dibujado d, patron p)
{
	glPushMatrix();
		if (dech)
			glRotatef(30,0,1,0);
		else
			glRotatef(-30,0,1,0);
		glRotatef(80,1,0,0);
		cil->draw(d,p);
	glPopMatrix();
}

void Cabeza::draw(dibujado d, patron p)
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glRotatef(120,0,1,0);

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
			glTranslatef(0,aperturaFauces,0);
			glRotatef(aperturaFauces*3,1,0,-1);
			glRotatef(cabezaSup,1,0,1);

			glPushMatrix();
				glScalef(2.1, 2.1, 2.1);
				glTranslatef(0, 9, 0);
				upperhead->draw(d,p);
				hair->draw(d,p);
			glPopMatrix();

			glPushMatrix();
				glRotatef(-120,0,1,0);
				glTranslatef(-10,15,21);
				ojo_izq->draw(d,p);
			glPopMatrix();

			glPushMatrix();
				glRotatef(-120,0,1,0);
				glTranslatef(10,15,21);
				ojo_dech->draw(d,p);
			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}