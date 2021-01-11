#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
	// leer la lista de caras y vértices
	ply::read( nombre_archivo, this->v, this->f );

	preparar_modos();
	setColor(Tupla3f(0.5f,0.25f,0.0f));
}