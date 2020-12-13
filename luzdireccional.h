#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz
{
protected:
	float alpha, beta;
	void rotacionEjeY();
	void rotacionEjeX();
	
public:
	LuzDireccional(const Tupla2f& orientacion, GLenum idLuz, const Tupla4f& cdifuso, const Tupla4f& cespecular, const Tupla4f& cambiente);
	void activar();
	inline void variarAnguloAlpha(float incremento) {
		alpha = incremento;
	}
	inline void variarAnguloBeta(float incremento) {
		beta = incremento;
	}
};

#endif