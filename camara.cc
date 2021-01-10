#include "camara.h"

void Camara::modificarVisualizacion(float left, float right, float bottom, float top, float near, float far)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->near = near;
	this->far = far;
}

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, float left, float right, float bottom, float top, float near, float far, tipoCamara tipo)
{
	this->eye = eye;
	this->at = at;
	this->up = up;
	modificarVisualizacion(left,right,bottom,top,near,far);
	this->tipo = tipo;
}

//examinar
void Camara::rotarXExaminar(float angle)
{
	Tupla3f vpn = eye - at;
	float modulo = sqrt(vpn.lengthSq());

	vpn[1] = vpn[1]*cos(angle) - vpn[2]*sin(angle);	
	vpn[2] = vpn[1]*sin(angle) + vpn[2]*cos(angle);

	up[1] = up[1]*cos(angle) - up[2]*sin(angle);	
	up[2] = up[1]*sin(angle) + up[2]*cos(angle);

	vpn = vpn.normalized()*modulo;

	eye = vpn + at;
}

void Camara::rotarYExaminar(float angle)
{
	Tupla3f vpn = eye - at;
	float modulo = sqrt(vpn.lengthSq());

	vpn[0] = vpn[2]*sin(angle) + vpn[0]*cos(angle);
	vpn[2] = vpn[2]*cos(angle) - vpn[0]*sin(angle);

	up[0] = up[2]*sin(angle) + up[0]*cos(angle);
	up[2] = up[2]*cos(angle) - up[0]*sin(angle);

	vpn = vpn.normalized()*modulo;

	eye = vpn + at;
}

void Camara::rotarZExaminar(float angle)
{
	Tupla3f vpn = eye - at;
	float modulo = sqrt(vpn.lengthSq());

	vpn[0] = vpn[0]*cos(angle) - vpn[1]*sin(angle);	
	vpn[1] = vpn[0]*sin(angle) + vpn[1]*cos(angle);

	up[0] = up[2]*sin(angle) + up[0]*cos(angle);
	up[2] = up[2]*cos(angle) - up[0]*sin(angle);

	vpn = vpn.normalized()*modulo;

	eye = vpn + at;
}

void Camara::rotarVerticalExaminar(float angle)
{

}

//firstperson
void Camara::rotarXFirstPerson(float angle)
{
	Tupla3f ateye = at - eye;
	float modulo = sqrt(ateye.lengthSq());

	ateye[1] = ateye[1]*cos(angle) - ateye[2]*sin(angle);	
	ateye[2] = ateye[1]*sin(angle) + ateye[2]*cos(angle);

	up[1] = up[1]*cos(angle) - up[2]*sin(angle);	
	up[2] = up[1]*sin(angle) + up[2]*cos(angle);

	ateye = ateye.normalized()*modulo;

	at = ateye - eye;
}

void Camara::rotarYFirstPerson(float angle)
{
	Tupla3f ateye = at - eye;
	float modulo = sqrt(ateye.lengthSq());

	ateye[0] = ateye[2]*sin(angle) + ateye[0]*cos(angle);
	ateye[2] = ateye[2]*cos(angle) - ateye[0]*sin(angle);

	up[0] = up[2]*sin(angle) + up[0]*cos(angle);
	up[2] = up[2]*cos(angle) - up[0]*sin(angle);

	ateye = ateye.normalized()*modulo;

	at = ateye - eye;
}

void Camara::rotarZFirstPerson(float angle)
{
	Tupla3f ateye = at - eye;
	float modulo = sqrt(ateye.lengthSq());

	ateye[0] = ateye[0]*cos(angle) - ateye[1]*sin(angle);	
	ateye[1] = ateye[0]*sin(angle) + ateye[1]*cos(angle);

	up[0] = up[2]*sin(angle) + up[0]*cos(angle);
	up[2] = up[2]*cos(angle) - up[0]*sin(angle);

	ateye = ateye.normalized()*modulo;

	at = ateye - eye;
}

void Camara::girar(int x, int y)
{
	rotarXFirstPerson(x); //no es así
	rotarYFirstPerson(y);
}

//

void Camara::zoom(float factor)
{
	left += factor;
	right -= factor;
	top -= factor;
	bottom += factor;
}

void Camara::setObserver() {
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
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