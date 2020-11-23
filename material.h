#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material 
{
private:
	Tupla4f difuso, especular, ambiente;
	float brillo;

public:
	Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float mbrillo);
	void aplicar();
};

#endif