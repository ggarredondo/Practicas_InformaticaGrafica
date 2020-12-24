#include "morsmanum.h"

Morsmanum::Morsmanum()
{
	torso = new ObjPLY("./morsmanum/ply/torso.ply");
	torso->setMaterial(Material({0.67,0.54,0.51,1},{0.01,0.01,0.01,1},{0,0,0,0},1));

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
			glTranslatef(0,8,3);
			glRotatef(cabezaX,1,0,0);
			glRotatef(cabezaY,0,1,0);
			glRotatef(cabezaZ,0,0,1);
			glRotatef(120,0,1,0);
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

void Morsmanum::rotarAntebrazoIzq(float y) {
	brazo_izq->rotarAntebrazo(y);
}

void Morsmanum::rotarManoIzq(float y, float z) {
	brazo_izq->rotarMano(y,z);
}

void Morsmanum::rotarDedosIzq(float z) {
	brazo_izq->rotarDedos(z);
}

void Morsmanum::rotarPulgarIzq(float y, float z) {
	brazo_izq->rotarPulgar(y,z);
}


//BrazoDech
void Morsmanum::rotarBrazoDech(float x, float y, float z) {
	BrazoDechX = x;
	BrazoDechY = y;
	BrazoDechZ = z;
}

void Morsmanum::rotarAntebrazoDech(float y) {
	brazo_dech->rotarAntebrazo(y);
}

void Morsmanum::rotarManoDech(float y, float z) {
	brazo_dech->rotarMano(y,z);
}

void Morsmanum::rotarDedosDech(float z) {
	brazo_dech->rotarDedos(z);
}

void Morsmanum::rotarPulgarDech(float y, float z) {
	brazo_dech->rotarPulgar(y,z);
}


//PiernaIzq
void Morsmanum::rotarPiernaIzq(float x, float y, float z) {
	PiernaIzqX = x;
	PiernaIzqY = y;
	PiernaIzqZ = z;
}

void Morsmanum::rotarRodillaIzq(float x) {
	pierna_izq->rotarRodilla(x);
}

void Morsmanum::rotarTalonIzq(float x) {
	pierna_izq->rotarTalon(x);
}


//PiernaDech
void Morsmanum::rotarPiernaDech(float x, float y, float z) {
	PiernaDechX = x;
	PiernaDechY = y;
	PiernaDechZ = z;
}

void Morsmanum::rotarRodillaDech(float x) {
	pierna_dech->rotarRodilla(x);
}

void Morsmanum::rotarTalonDech(float x) {
	pierna_dech->rotarTalon(x);
}