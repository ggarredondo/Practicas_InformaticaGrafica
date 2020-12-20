#include "morsmanum.h"

Morsmanum::Morsmanum()
{
	torso = new ObjPLY("./morsmanum/ply/torso.ply");
	cabeza = new Cabeza();
	brazo_izq = new BrazoIzq();
	brazo_dech = new BrazoDech();
	pierna_izq = new PiernaIzq();
	pierna_dech = new PiernaDech();

	cabezaX = 0;
	cabezaY = 0;
	cabezaZ = 0;

	torsoX = 0;
	torsoY = 0;
	torsoZ = 0;

	BrazoIzqX = 0; 
	BrazoIzqY = 0;
	BrazoIzqZ = 0;

	BrazoDechX = 0;
	BrazoDechY = 0; 
	BrazoDechZ = 0;

	PiernaIzqX = 0;
	PiernaIzqY = 0;
	PiernaIzqZ = 0;

	PiernaDechX = 0; 
	PiernaDechY = 0;
	PiernaDechZ = 0;
}

void Morsmanum::draw(dibujado d, patron p)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(0,70,0);
			
		glPushMatrix();
			glTranslatef(0,10,-3);
			glRotatef(120,0,1,0);
			glRotatef(cabezaX,1,0,0);
			glRotatef(cabezaY,0,1,0);
			glRotatef(cabezaZ,0,0,1);
			cabeza->draw(d,p);
		glPopMatrix();

		glScalef(13,13,13);
		glRotatef(torsoX,1,0,0);
		glRotatef(torsoY,0,1,0);
		glRotatef(torsoZ,0,0,1);
		torso->draw(d,p);

		glPushMatrix();
			glTranslatef(1.9,-1.1,-0.1);
			glRotatef(BrazoIzqX,1,0,0);
			glRotatef(BrazoIzqY,0,1,0);
			glRotatef(BrazoIzqZ,0,0,1);
			brazo_izq->draw(d,p);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.9,-1.1,-0.1);
			glRotatef(BrazoDechX,1,0,0);
			glRotatef(BrazoDechY,0,1,0);
			glRotatef(BrazoDechZ,0,0,1);
			brazo_dech->draw(d,p);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1,-7.1,-0.7);
			glRotatef(PiernaIzqX,1,0,0);
			glRotatef(PiernaIzqY,0,1,0);
			glRotatef(PiernaIzqZ,0,0,1);
			pierna_izq->draw(d,p);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1,-7.1,-0.7);
			glRotatef(PiernaDechX,1,0,0);
			glRotatef(PiernaDechY,0,1,0);
			glRotatef(PiernaDechZ,0,0,1);
			pierna_dech->draw(d,p);
		glPopMatrix();

	glPopMatrix();
}

//Cabeza
void Morsmanum::rotarCabeza(float x, float y, float z) {
	cabezaX = x;
	cabezaY = y;
	cabezaZ = z;
}

void Morsmanum::abrirFauces(float apertura) {
	cabeza->abrirFauces(apertura);
}


//Torso
void Morsmanum::rotarTorso(float x, float y, float z) {
	torsoX = x;
	torsoY = y;
	torsoZ = z;
}


//BrazoIzq
void Morsmanum::rotarBrazoIzq(float x, float y, float z) {
	BrazoIzqX = x;
	BrazoIzqY = y;
	BrazoIzqZ = z;
}


//BrazoDech
void Morsmanum::rotarBrazoDech(float x, float y, float z) {
	BrazoDechX = x;
	BrazoDechY = y;
	BrazoDechZ = z;
}


//PiernaIzq
void Morsmanum::rotarPiernaIzq(float x, float y, float z) {
	PiernaIzqX = x;
	PiernaIzqY = y;
	PiernaIzqZ = z;
}


//PiernaDech
void Morsmanum::rotarPiernaDech(float x, float y, float z) {
	PiernaDechX = x;
	PiernaDechY = y;
	PiernaDechZ = z;
}