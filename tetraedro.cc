#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{
	double h = 90;

	// inicializar la tabla de vértices
	v = { {h*sqrt(3)/3, -h/4, -h/3}, //A
			{0, -h/4, h*2/3}, //B
			{-h*sqrt(3)/3, -h/4, -h/3}, //C
			{0, 3*h/4, 0} }; //H

	// inicializar la tabla de caras o triángulos:
	// (es importante en cada cara ordenar los vértices en sentido contrario
	//  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

	f = { {2, 0, 1}, 
			{1, 3, 2},
			{3, 0, 2},
			{0, 3, 1} };
			
    preparar_modos();
}