#include "camara.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, float left, float right, float bottom, float top, float near, float far, tipoCamara tipo)
{
	this->eye = eye;
	this->at = at;
	this->up = up;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->near = near;
	this->far = far;
	this->tipo = tipo;
}

//examinar
void Camara::rotarXExaminar(float angle)
{
	eye[1] = eye[1]*cos(angle) - eye[2]*sin(angle);	
	eye[2] = eye[1]*sin(angle) + eye[2]*cos(angle);
}

void Camara::rotarYExaminar(float angle)
{
	eye[0] = eye[2]*sin(angle) + eye[0]*cos(angle);
	eye[2] = eye[2]*cos(angle) - eye[0]*sin(angle);
}

void Camara::rotarZExaminar(float angle)
{
	eye[0] = eye[0]*cos(angle) - eye[1]*sin(angle);	
	eye[1] = eye[0]*sin(angle) + eye[1]*cos(angle);
}

//firstperson
void Camara::rotarXFirstPerson(float angle)
{
	at[1] = at[1]*cos(angle) - at[2]*sin(angle);	
	at[2] = at[1]*sin(angle) + at[2]*cos(angle);
}

void Camara::rotarYFirstPerson(float angle)
{
	at[0] = at[2]*sin(angle) + at[0]*cos(angle);
	at[2] = at[2]*cos(angle) - at[0]*sin(angle);
}

void Camara::rotarZFirstPerson(float angle)
{
	at[0] = at[0]*cos(angle) - at[1]*sin(angle);	
	at[1] = at[0]*sin(angle) + at[1]*cos(angle);
}

//

void Camara::zoom(float factor)
{
	left -= factor;
	right -= factor;
	top -= factor;
	bottom -= factor;
}

void Camara::setObserver() {
	gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]);
}

void Camara::setProyeccion()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (tipo == ORTOGONAL)
		glOrtho(left,right,bottom,top,near,far);
	else
		glFrustum(left,right,bottom,top,near,far);
}