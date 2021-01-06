#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, bool tapas, std::string tex)
{
	std::vector<Tupla3f> perfil;
	int n = num_vert_perfil-1;

	if (n >= 0)
		perfil.push_back(Tupla3f(radio, 0, 0));
	for (int i = 1; i <= n; ++i) {
		perfil.push_back(Tupla3f(radio, altura*i/n, 0));
	}

	if (n >= 0)
		prepararObj(perfil, num_instancias_perf, tapas, tex);
}