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

		glPushMatrix();
			glScalef(13,13,13);
			glTranslatef(0,10,0); //temp
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

	glPopMatrix();
}