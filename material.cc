#include "material.h"

Material::Material()
{
	difuso = Tupla4f(1,1,1,1);
	especular = Tupla4f(0,0,0,0);
	ambiente = Tupla4f(0,0,0,0);
	brillo = 1;
}

Material::Material(const Tupla4f& mdifuso, const Tupla4f& mespecular, const Tupla4f& mambiente, float mbrillo)
{
	difuso = mdifuso;
	especular = mespecular;
	ambiente = mambiente;
	brillo = mbrillo;
}

void Material::aplicar()
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialf(GL_FRONT, GL_SHININESS, brillo);
}