#ifndef SKYSPHERE_H_INCLUDED
#define SKYSPHERE_H_INCLUDED

#include "objrevolucion.h"

class Skysphere : public ObjRevolucion
{
public:
	Skysphere(const int num_vert_perfil, const int num_instancias_perf, const float radio, std::string tex);
};

#endif