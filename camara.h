#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {ORTOGONAL, PERSPECTIVA} tipoCamara;
typedef enum {NULO, EXAMINAR, FIRSTPERSON} camara;

class Camara
{
private:
	Tupla3f eye, at, up;
	tipoCamara tipo;
	float left, right, bottom, top, near, far;

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
	void rotarVerticalFirstPerson(float angle);
	void girar(int x, int y, camara c);

	inline void mover(float x, float y, float z) {
		eye = eye + Tupla3f(x,y,z);
	}
	void moverAdelante(float valor);
	void moverLateral(float valor);

	void zoom(float factor);

	void setObserver();
	void setProyeccion();

	inline void setAt(Tupla3f at) {
		this->at = at;
	}
};

#endif