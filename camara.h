#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {ORTOGONAL, PERSPECTIVA} tipoCamara;

class Camara
{
private:
	Tupla3f eye, at, up, vpn;
	tipoCamara tipo;
	float left, right, bottom, top, near, far;
	float angleY;

public:
	Camara(Tupla3f eye, Tupla3f at, Tupla3f up, float left, float right, float bottom, float top, float near, float far, tipoCamara tipo);
	void modificarVisualizacion(float left, float right, float bottom, float top, float near, float far);

	void rotarXExaminar(float angle);
	void rotarYExaminar(float angle);
	void rotarZExaminar(float angle);
	void rotarVerticalExaminar(float angle);

	void rotarXFirstPerson(float angle);
	void rotarYFirstPerson(float angle);
	void rotarZFirstPerson(float angle);
	void girar(int x, int y);

	inline void mover(float x, float y, float z) {
		eye = eye + Tupla3f(x,y,z);
	}
	void zoom(float factor);

	void setObserver();
	void setProyeccion();

	inline Camara& operator=(const Camara& c) {
		at = c.at;
		return *this;
	}
};

#endif