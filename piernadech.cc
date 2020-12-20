#include "piernadech.h"

PiernaDech::PiernaDech()
{
	thigh = new ObjPLY("./morsmanum/ply/Rleg.ply");
	lowerleg = new ObjPLY("./morsmanum/ply/Rshin.ply");
	foot = new ObjPLY("./morsmanum/ply/Rfoot.ply");

	PiernaInfX = 0;
	PieX = 0;
}

void PiernaDech::draw(dibujado d, patron p)
{
	glPushMatrix();
		thigh->draw(d,p);
		
		glTranslatef(0.1,-3.6,0.1);
		glRotatef(PiernaInfX,1,0,0);
		lowerleg->draw(d,p);
			
		glTranslatef(0.3,-4,-0.6);
		glRotatef(PieX,1,0,0);
		foot->draw(d,p);

	glPopMatrix();
}