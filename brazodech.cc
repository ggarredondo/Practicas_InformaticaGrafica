#include "brazodech.h"

BrazoDech::BrazoDech() 
{
	shoulder = new ObjPLY("./morsmanum/ply/Rarm.ply");
	shoulder->setMaterial(Material({0.67,0.54,0.51,1},{0.01,0.01,0.01,1},{0,0,0,0},1));
	forearm = new ObjPLY("./morsmanum/ply/Rforearm.ply");
	forearm->setMaterial(Material({0.67,0.54,0.51,1},{0.01,0.01,0.01,1},{0,0,0,0},1));
	hand = new ObjPLY("./morsmanum/ply/Rhand.ply");
	hand->setMaterial(Material({0.67,0.54,0.51,1},{0.01,0.01,0.01,1},{0,0,0,0},1));
	fingers = new ObjPLY("./morsmanum/ply/Rfingers.ply");
	fingers->setMaterial(Material({0.67,0.54,0.51,1},{0.01,0.01,0.01,1},{0,0,0,0},1));
	thumb = new ObjPLY("./morsmanum/ply/Rthumb.ply");
	thumb->setMaterial(Material({0.67,0.54,0.51,1},{0.01,0.01,0.01,1},{0,0,0,0},1));

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