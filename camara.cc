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

inline void rotarEjeX(Tupla3f& t, float angle) {
	t[1] = t[1]*cos(angle) - t[2]*sin(angle);	
	t[2] = t[1]*sin(angle) + t[2]*cos(angle);
}

inline void rotarEjeY(Tupla3f& t, float angle) {
	t[0] = t[2]*sin(angle) + t[0]*cos(angle);
	t[2] = t[2]*cos(angle) - t[0]*sin(angle);
}

inline void rotarEjeZ(Tupla3f& t, float angle) {
	t[0] = t[0]*cos(angle) - t[1]*sin(angle);	
	t[1] = t[0]*sin(angle) + t[1]*cos(angle);
}

//examinar
void Camara::rotarXExaminar(float angle)
{
	Tupla3f vpn = eye-at;
	float modulo = sqrt(vpn.lengthSq());

	rotarEjeX(vpn, angle);
	rotarEjeX(up, angle);

	vpn = vpn.normalized()*modulo;

	eye = vpn + at;
}

void Camara::rotarYExaminar(float angle)
{
	Tupla3f vpn = eye-at;
	float modulo = sqrt(vpn.lengthSq());

	rotarEjeY(vpn, angle);
	rotarEjeY(up, angle);

	vpn = vpn.normalized()*modulo;

	eye = vpn + at;
}

void Camara::rotarZExaminar(float angle)
{
	Tupla3f vpn = eye-at;
	float modulo = sqrt(vpn.lengthSq());

	rotarEjeZ(vpn, angle);
	rotarEjeZ(up, angle);

	vpn = vpn.normalized()*modulo;

	eye = vpn + at;
}

void Camara::rotarVerticalExaminar(float angle)
{
	Tupla3f vpn = eye-at;
	GLfloat distance = sqrt((vpn).lengthSq());
	rotarXExaminar(angle*vpn[2]/distance);
	rotarZExaminar(-angle*vpn[0]/distance);
}

//firstperson
void Camara::rotarXFirstPerson(float angle)
{
	Tupla3f ateye = at - eye;
	float modulo = sqrt(ateye.lengthSq());

	rotarEjeX(ateye, angle);
	rotarEjeX(up, angle);

	ateye = ateye.normalized()*modulo;

	at = ateye + eye;
}

void Camara::rotarYFirstPerson(float angle)
{
	Tupla3f ateye = at - eye;
	float modulo = sqrt(ateye.lengthSq());

	rotarEjeY(ateye, angle);
	rotarEjeY(up, angle);

	ateye = ateye.normalized()*modulo;

	at = ateye + eye;
}

void Camara::rotarZFirstPerson(float angle)
{
	Tupla3f ateye = at - eye;
	float modulo = sqrt(ateye.lengthSq());

	rotarEjeZ(ateye, angle);
	rotarEjeZ(up, angle);

	ateye = ateye.normalized()*modulo;

	at = ateye + eye;
}

void Camara::rotarVerticalFirstPerson(float angle)
{
	Tupla3f ateye = at-eye;
	GLfloat distance = sqrt((at-eye).lengthSq());
	rotarXFirstPerson(angle*ateye[2]/distance);
	rotarZFirstPerson(-angle*ateye[0]/distance); 
}

void Camara::girar(int x, int y, camara c)
{ 
	float a = y*M_PI/180, b = x*M_PI/180;
	if (c == FIRSTPERSON) {
		rotarVerticalFirstPerson(a);
		rotarYFirstPerson(-b);
	}
	else if (c == EXAMINAR) {
		rotarVerticalExaminar(a);
		rotarYExaminar(b);
	}
}

//

void Camara::moverAdelante(float valor)
{
	Tupla3f ateye = at - eye;
	eye = eye + ateye*valor;
	at = at + ateye*valor;
}

void Camara::moverLateral(float valor)
{
	Tupla3f u = up.cross(eye-at);

	eye = eye + u*valor;
	at = at + u*valor;
}

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