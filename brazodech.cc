#include "brazodech.h"

BrazoDech::BrazoDech() 
{
	shoulder = new ObjPLY("./morsmanum/ply/Rarm.ply");
	forearm = new ObjPLY("./morsmanum/ply/Rforearm.ply");
	hand = new ObjPLY("./morsmanum/ply/Rhand.ply");
	fingers = new ObjPLY("./morsmanum/ply/Rfingers.ply");
	thumb = new ObjPLY("./morsmanum/ply/Rthumb.ply");
}

void BrazoDech::draw(dibujado d, patron p)
{	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		shoulder->draw(d,p);

		glTranslatef(-3.72,-0.4,-0.15);
		forearm->draw(d,p);

		glTranslatef(-3.36,0.1,0.65);
		hand->draw(d,p);
				
		glPushMatrix();	
			glTranslatef(-2.16,0.2,0.15);
			fingers->draw(d,p);
		glPopMatrix();
					
		glPushMatrix();	
			glTranslatef(-1.8,-0.7,1.0);
			thumb->draw(d,p);
		glPopMatrix();

	glPopMatrix();
}