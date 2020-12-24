#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material 
{
private:
	Tupla4f difuso, especular, ambiente;
	float brillo;

public:
	Material();
	Material(const Tupla4f& mdifuso, const Tupla4f& mespecular, const Tupla4f& mambiente, float mbrillo);
	void aplicar();
};

#endif