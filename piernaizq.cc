#include "piernaizq.h"

PiernaIzq::PiernaIzq()
{
	thigh = new ObjPLY("./morsmanum/ply/leg.ply");
	lowerleg = new ObjPLY("./morsmanum/ply/shin.ply");
	foot = new ObjPLY("./morsmanum/ply/foot.ply");
}

void PiernaIzq::draw(dibujado d, patron p)
{
	glPushMatrix();
		thigh->draw(d,p);

		glPushMatrix();
			glTranslatef(-0.1,-3.6,0.1);
			lowerleg->draw(d,p);

			glPushMatrix();
				glTranslatef(-0.3,-4,-0.6);
				foot->draw(d,p);
			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}