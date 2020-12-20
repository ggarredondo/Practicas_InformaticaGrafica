#include "piernaizq.h"

PiernaIzq::PiernaIzq()
{
	thigh = new ObjPLY("./morsmanum/ply/leg.ply");
	lowerleg = new ObjPLY("./morsmanum/ply/shin.ply");
	foot = new ObjPLY("./morsmanum/ply/foot.ply");

	PiernaInfX = 0;
	PieX = 0;
}

void PiernaIzq::draw(dibujado d, patron p)
{
	glPushMatrix();
		thigh->draw(d,p);

		glTranslatef(-0.1,-3.6,0.1);
		glRotatef(PiernaInfX,1,0,0);
		lowerleg->draw(d,p);
			
		glTranslatef(-0.3,-4,-0.6);
		glRotatef(PieX,1,0,0);
		foot->draw(d,p);

	glPopMatrix();
}