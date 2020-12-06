#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz
{
protected:
	float alpha, beta;
	void rotacionEjeY() {
		posicion[0] = posicion[2]*sin(alpha) + posicion[0]*cos(alpha);
		posicion[2] = posicion[2]*cos(alpha) - posicion[0]*sin(alpha);
		alpha = 0;
	}
	void rotacionEjeX() {
		posicion[1] = posicion[1]*cos(beta) - posicion[2]*sin(beta);	
		posicion[2] = posicion[1]*sin(beta) + posicion[2]*cos(beta);
		beta = 0;
	}

public:
	LuzDireccional(const Tupla2f& orientacion, GLenum idLuz, const Tupla4f& cdifuso, const Tupla4f& cespecular, const Tupla4f& cambiente);
	void activar();
	inline void variarAnguloAlpha(float incremento) {
		alpha += incremento;
	}
	inline void variarAnguloBeta(float incremento) {
		beta += incremento;
	}
};

#endif