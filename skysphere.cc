#include "skysphere.h"

Skysphere::Skysphere(const int num_vert_perfil, const int num_instancias_perf, const float radio, std::string tex) 
{
	std::vector<Tupla3f> perfil;
	int n = num_vert_perfil, mitad = n*0.5;

	for (int i = 0; i < mitad; ++i)
		perfil.push_back(Tupla3f(radio*cos(M_PI*i/n), radio*sin(M_PI*i/n), 0));

	if (n > 0)
		prepararObj(perfil, num_instancias_perf, true, tex, true);
}