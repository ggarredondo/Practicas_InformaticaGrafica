#include "brazoizq.h"

BrazoIzq::BrazoIzq() 
{
	shoulder = new ObjPLY("./morsmanum/ply/arm.ply");
	forearm = new ObjPLY("./morsmanum/ply/forearm.ply");
	hand = new ObjPLY("./morsmanum/ply/hand.ply");
	fingers = new ObjPLY("./morsmanum/ply/fingers.ply");
	thumb = new ObjPLY("./morsmanum/ply/thumb.ply");
}

void BrazoIzq::draw(dibujado d, patron p)
{	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		shoulder->draw(d,p);

		glPushMatrix();
			glTranslatef(3.1,-0.4,-0.15);
			forearm->draw(d,p);

			glPushMatrix();
				glTranslatef(2.8,0.1,0.65);
				hand->draw(d,p);

				glPushMatrix();
					glTranslatef(1.8,0.2,0.15);
					fingers->draw(d,p);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(1.5,-0.7,1.0);
					thumb->draw(d,p);
				glPopMatrix();
			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}