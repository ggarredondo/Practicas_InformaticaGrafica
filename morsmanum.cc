#include "morsmanum.h"

Morsmanum::Morsmanum()
{
	torso = new ObjPLY("./morsmanum/ply/torso.ply");
	cabeza = new Cabeza();
	brazo_izq = new BrazoIzq();
	brazo_dech = new BrazoDech();
	pierna_izq = new PiernaIzq();
	pierna_dech = new PiernaDech();
}

void Morsmanum::draw(dibujado d, patron p)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(0,70,0);
			
		glPushMatrix();
			glTranslatef(0,10,-3);
			glRotatef(120,0,1,0);
			cabeza->draw(d,p);
		glPopMatrix();

		glScalef(13,13,13);
		torso->draw(d,p);

		glPushMatrix();
			glTranslatef(1.9,-1.1,-0.1);
			brazo_izq->draw(d,p);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.9,-1.1,-0.1);
			brazo_dech->draw(d,p);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1,-7.1,-0.7);
			pierna_izq->draw(d,p);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1,-7.1,-0.7);
			pierna_dech->draw(d,p);
		glPopMatrix();

	glPopMatrix();
}