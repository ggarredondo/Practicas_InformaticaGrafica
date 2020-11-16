#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, bool tapa_sup, bool tapa_inf)
{
	std::vector<Tupla3f> perfil;
	int n = num_vert_perfil-1;

	if (n >= 0)
		perfil.push_back(Tupla3f(radio, 0, 0));
	for (int i = 1; i <= n; ++i) {
		perfil.push_back(Tupla3f(radio, altura*i/n, 0));
		//std::cout << radio << " " << altura*i/n << " " << 0 << std::endl;
	}

	if (n >= 0) {
		crearMalla(perfil, num_instancias_perf);
	    insertarPolos(perfil, num_instancias_perf, tapa_sup, tapa_inf);
		preparar_modos();
	}
}