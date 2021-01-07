#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {ORTOGONAL, PERSPECTIVA} tipoCamara;

class Camara
{
private:
	Tupla3f eye, at, up;
	tipoCamara tipo;
	float left, right, bottom, top, near, far;

public:
	Camara();

	void rotarXExaminar(float angle);
	void rotarYExaminar(float angle);
	void rotarZExaminar(float angle);

	void rotarXFirstPerson(float angle);
	void rotarYFirstPerson(float angle);
	void rotarZFirstPerson(float angle);

	void mover(float x, float y, float z);
	void zoom(float factor);

	void setObserver();
	void setProyeccion();
};

#endif