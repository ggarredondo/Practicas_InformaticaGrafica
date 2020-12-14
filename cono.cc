#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, bool tapas)
{
	std::vector<Tupla3f> perfil;
	int n = num_vert_perfil-1;
	float r;

	
	perfil.push_back(Tupla3f(radio, 0, 0));
	for (int i = n; i > 0; --i) {
		r = (n-i+1.0f)/i;
		perfil.push_back(Tupla3f(radio/(1.0f+r), altura*r/(1.0f+r), 0));
	}

	if (n >= 0)
		prepararObj(perfil, num_instancias_perf, tapas);
}