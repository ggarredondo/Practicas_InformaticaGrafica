#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
	std::vector<Tupla3f> vertices;
	ply::read_vertices(archivo, vertices);
	crearMalla(vertices, num_instancias);
	insertarPolos(vertices, num_instancias, tapa_sup, tapa_inf);
	preparar_modos();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(const std::vector<Tupla3f>& archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    crearMalla(archivo, num_instancias);
    insertarPolos(archivo, num_instancias, tapa_sup, tapa_inf);
	preparar_modos();
}

void ObjRevolucion::crearMalla(const std::vector<Tupla3f>& perfil_original, int num_instancias) {
	Tupla3f v_aux;
	unsigned N = num_instancias, M = perfil_original.size();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			v_aux = perfil_original[j];
			v_aux[2] = -v_aux[0]*sin(2*M_PI*i/N);
			v_aux[0] *= cos(2*M_PI*i/N);
			v.push_back(v_aux);
		}
	}

	unsigned a, b;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M-1; ++j) {
			a = M*i + j;
			b = M*((i+1)%N)+j;
			f.push_back(Tupla3i(a, b, b+1));
			f.push_back(Tupla3i(a, b+1, a+1));
		}
	}
}

void ObjRevolucion::insertarPolos(const std::vector<Tupla3f>& perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf)
{
	float min_h = perfil_original[0][1], max_h = perfil_original[perfil_original.size()-1][1];

	v.push_back(Tupla3f{0, min_h, 0});
	v.push_back(Tupla3f{0, max_h, 0});

	//formar tapas
	int sur = v.size()-2, norte = v.size()-1, anterior = -1, primero, N = num_instancias, M = perfil_original.size();

	if (tapa_inf) {
		for (unsigned i = 0; i < N; ++i) {
				if (anterior == -1)
					primero = M*i;
				if (anterior != -1)
					f.push_back(Tupla3i(sur, M*i, anterior));
				anterior = M*i;
		}
		f.push_back(Tupla3i(sur, primero, anterior));
	}

	if (tapa_sup) {
		anterior = -1;
		for (unsigned i = 0; i < N; ++i) {
				if (anterior == -1)
					primero = M*(i+1)-1;
				if (anterior != -1) 
					f.push_back(Tupla3i(anterior, M*(i+1)-1, norte));
				anterior = M*(i+1)-1;
		}
		f.push_back(Tupla3i(anterior, primero, norte));
	}
}