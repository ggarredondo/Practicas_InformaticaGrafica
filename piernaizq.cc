#include "piernaizq.h"

PiernaIzq::PiernaIzq()
{
	thigh = new ObjPLY("./morsmanum/ply/leg.ply");
	thigh->setMaterial(Material({0.67,0.54,0.51,1},{0.01,0.01,0.01,1},{0,0,0,0},1));
	lowerleg = new ObjPLY("./morsmanum/ply/shin.ply");
	lowerleg->setMaterial(Material({0.67,0.54,0.51,1},{0.01,0.01,0.01,1},{0,0,0,0},1));
	foot = new ObjPLY("./morsmanum/ply/foot.ply");
	foot->setMaterial(Material({0.67,0.54,0.51,1},{0.01,0.01,0.01,1},{0,0,0,0},1));

	PiernaInfX = 0;
	PiernaInfY = 0;
	PiernaInfZ = 0;

	PieX = 0;
	PieY = 0;
	PieZ = 0;
}

void PiernaIzq::draw(dibujado d, patron p)
{
	glPushMatrix();
		thigh->draw(d,p);

		glTranslatef(-0.1,-3.6,0.1);
		glRotatef(PiernaInfX,1,0,0);
		glRotatef(PiernaInfY,0,1,0);
		glRotatef(PiernaInfZ,0,0,1);
		lowerleg->draw(d,p);
			
		glTranslatef(-0.3,-4,-0.6);
		glRotatef(PieX,1,0,0);
		glRotatef(PieY,0,1,0);
		glRotatef(PieZ,0,0,1);
		foot->draw(d,p);

	glPopMatrix();
}