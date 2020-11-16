#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, bool tapa_sup, bool tapa_inf)
{
	std::vector<Tupla3f> perfil;
	int n = num_vert_perfil;

	float r, x, y;
	for (int i = n; i > 0; --i) {
		r = (n-i+1)/i;
		perfil.push_back(Tupla3f(radio/(1+r), altura*r/(1+r), 0));
		std::cout << radio/(1+r) << " " << altura*r/(1+r) << " " << 0 << std::endl;
	}

	crearMalla(perfil, num_instancias_perf);
    insertarPolos(perfil, num_instancias_perf, tapa_sup, tapa_inf);
	preparar_modos();
}