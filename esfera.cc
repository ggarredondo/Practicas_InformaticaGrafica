#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
	std::vector<Tupla3f> perfil;
	int n = num_vert_perfil;

	for (int i = 0; i < n; ++i)
		perfil.push_back(Tupla3f(radio*cos(2*M_PI*i/n), -radio*sin(2*M_PI*i/n), 0));

	crearMalla(perfil, num_instancias_perf);
	preparar_modos();
}