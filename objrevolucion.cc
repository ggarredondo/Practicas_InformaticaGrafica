#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <algorithm>


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas, std::string tex) {
	std::vector<Tupla3f> vertices;
	ply::read_vertices(archivo, vertices);

	if (vertices[0][1] > vertices[vertices.size()-1][1])
		std::reverse(vertices.begin(), vertices.end());
	if (tex.compare("n") != 0)
		textura = new Textura(tex);
	prepararObj(vertices, num_instancias, tapas);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(const std::vector<Tupla3f>& archivo, int num_instancias, bool tapas) {
    prepararObj(archivo, num_instancias, tapas);
}

void ObjRevolucion::actualizarTapas(bool tapas) {
	if (!tapas) {
		tam1 -= size_tapas;
		diferencia = size_tapas;
	}
	else {
		tam1 += diferencia;
		diferencia = 0;
	}
	tamA = tam1*0.5;
	tamB = tam1-tamA;
}

void ObjRevolucion::prepararObj(const std::vector<Tupla3f>& perfil, int num_instancias, bool tapas) {
	crearMalla(perfil, num_instancias);
	if (textura != nullptr)
		calcularCoordTextura(num_instancias, perfil.size());
    insertarPolos(perfil, num_instancias);
	preparar_modos();
	actualizarTapas(tapas);
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
	if (textura) {
		for (unsigned j = 0; j < M; ++j)
			v.push_back(v[j]);
		N++;
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

void ObjRevolucion::insertarPolos(const std::vector<Tupla3f>& perfil_original, int num_instancias)
{
	float min_h = perfil_original[0][1], max_h = perfil_original[perfil_original.size()-1][1];

	//formar tapas
	int polo = v.size(), anterior = -1, primero, N = num_instancias, M = perfil_original.size();

	v.push_back(Tupla3f{0, min_h, 0});
	for (unsigned i = 0; i < N; ++i) {
			if (anterior == -1)
				primero = M*i;
			if (anterior != -1) {
				f.push_back(Tupla3i(polo, M*i, anterior));
				size_tapas++;
			}
			anterior = M*i;
	}
	f.push_back(Tupla3i(polo, primero, anterior));
	size_tapas++;

	polo = v.size();
	v.push_back(Tupla3f{0, max_h, 0});
	anterior = -1;
	for (unsigned i = 0; i < N; ++i) {
			if (anterior == -1)
				primero = M*(i+1)-1;
			if (anterior != -1) {
				f.push_back(Tupla3i(anterior, M*(i+1)-1, polo));
				size_tapas++;
			}
			anterior = M*(i+1)-1;
	}
	f.push_back(Tupla3i(anterior, primero, polo));
	size_tapas++;
}

inline float modulo(const Tupla3f& t) {
	return sqrt( t[0]*t[0] + t[1]*t[1] + t[2]*t[2] );
}

void ObjRevolucion::calcularCoordTextura(unsigned N, unsigned M)
{
	ct.resize(v.size());
	std::vector<float> d(M,0);
	N++;

	for (unsigned i = 1; i < M; ++i) 
		d[i] = d[i-1] + modulo(v[0]-v[i]);

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j)
			ct[j+M*i] = { i/(N-1.0), 1-d[j]/d[M-1] };
	}
}