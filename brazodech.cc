#include "brazodech.h"

BrazoDech::BrazoDech() 
{
	shoulder = new ObjPLY("./morsmanum/ply/Rarm.ply");
	shoulder->setTextura("./texturas/redead1.jpg");
	forearm = new ObjPLY("./morsmanum/ply/Rforearm.ply");
	forearm->setTextura("./texturas/redead1.jpg");
	hand = new ObjPLY("./morsmanum/ply/Rhand.ply");
	hand->setTextura("./texturas/redead1.jpg");
	fingers = new ObjPLY("./morsmanum/ply/Rfingers.ply");
	fingers->setTextura("./texturas/redead1.jpg");
	thumb = new ObjPLY("./morsmanum/ply/Rthumb.ply");
	thumb->setTextura("./texturas/redead1.jpg");

	AntebrazoY = 0;
	ManoY = 0;
	ManoZ = 0;
	DedosZ = 0;
	PulgarY = 0;
	PulgarZ = 0;
}

void BrazoDech::draw(dibujado d, patron p)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		shoulder->draw(d,p);

		glTranslatef(-3.72,-0.4,-0.15);
		glRotatef(AntebrazoY,0,1,0);
		forearm->draw(d,p);

		glTranslatef(-3.36,0.1,0.65);
		glRotatef(ManoY,0,1,0);
		glRotatef(ManoZ,0,0,1);
		hand->draw(d,p);
				
		glPushMatrix();	
			glTranslatef(-2.16,0.2,0.15);
			glRotatef(DedosZ,0,0,1);
			fingers->draw(d,p);
		glPopMatrix();
					
		glPushMatrix();	
			glTranslatef(-1.8,-0.7,1.0);
			glRotatef(PulgarY,0,1,0);
			glRotatef(PulgarZ,0,0,1);
			thumb->draw(d,p);
		glPopMatrix();

	glPopMatrix();
}