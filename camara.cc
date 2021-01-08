#include "camara.h"

Camara::Camara() 
{

}

void Camara::rotarXExaminar(float angle)
{

}

void Camara::rotarYExaminar(float angle)
{

}

void Camara::rotarZExaminar(float angle)
{

}

void Camara::rotarXFirstPerson(float angle)
{

}

void Camara::rotarYFirstPerson(float angle)
{

}

void Camara::rotarZFirstPerson(float angle)
{

}

void Camara::mover(float x, float y, float z)
{

}

void Camara::zoom(float factor)
{
	//seguramente sea near += factor; Pues no
}

void Camara::setObserver() {
	gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]);
}

void Camara::setProyeccion()
{
	glMatrixMode(GL_PROJECTION);
	if (tipo == ORTOGONAL)
		glOrtho(left,right,bottom,top,near,far);
	else
		glFrustum(left,right,bottom,top,near,far);
}