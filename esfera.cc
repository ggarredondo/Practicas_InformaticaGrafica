#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio, bool tapa_sup, bool tapa_inf)
{
	std::vector<Tupla3f> perfil;
	int n = num_vert_perfil, mitad = n*0.5;

	for (int i = mitad-1; i > 0; --i) {
		perfil.push_back(Tupla3f(radio*cos(M_PI*i/n), -radio*sin(M_PI*i/n), 0));
		//std::cout << radio*cos(M_PI*i/n) << " " << -radio*sin(M_PI*i/n) << " " << std::endl;
	}
	for (int i = 0; i < mitad; ++i) {
		perfil.push_back(Tupla3f(radio*cos(M_PI*i/n), radio*sin(M_PI*i/n), 0));
		//std::cout << radio*cos(M_PI*i/n) << " " << radio*sin(M_PI*i/n) << " " << std::endl;
	}

	if (n > 0) {
		crearMalla(perfil, num_instancias_perf);
		insertarPolos(perfil, num_instancias_perf, tapa_sup, tapa_inf);
		preparar_modos();
	}
}