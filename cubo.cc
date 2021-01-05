#include "cubo.h"

Cubo::Cubo(float lado)
{
	lado *= 0.5;
	// inicializar la tabla de vértices
	v = {   {-lado, -lado, lado},
			{lado, -lado, lado}, 
			{-lado, lado, lado},
			{lado, lado, lado},
			{-lado, -lado, -lado},
			{lado, -lado, -lado},
			{-lado, lado, -lado},
			{lado, lado, -lado} };

	// inicializar la tabla de caras o triángulos:
	// (es importante en cada cara ordenar los vértices en sentido contrario
	//  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
	f = {   {0, 1, 2},
			{2, 1, 3},
			{2, 3, 7},
			{7, 6, 2},
			{7, 3, 1},
			{7, 1, 5},
			{7, 4, 6},
			{7, 5, 4},
			{0, 4, 1},
			{1, 4, 5},
			{6, 4, 2},
			{2, 4, 0} };
	                     
	preparar_modos();
}