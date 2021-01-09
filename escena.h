#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "cubo.h"
#include "esfera.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include <map>
#include "morsmanum.h"
#include "cuadro.h"
#include "skysphere.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO, SELVISUALIZACION, SELDIBUJADO, ANIM, MANUAL} menu;
typedef enum {NINGUNO, ALFA, BETA} angulo;
typedef enum {EXAMINAR, FIRSTPERSON} camara;

class Escena
{

	private:
	// ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
	   
	   // variables que definen la posicion de la camara en coordenadas polares
	GLfloat Observer_distance;

	// variables que controlan la ventana y la transformacion de perspectiva
	GLfloat Width, Height, Front_plane, Back_plane;

	// Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
	void actualizarTapas();
	void pose_idle();

	void clear_window();

	//variables de estado para el menú
	menu modoMenu=NADA;
	dibujado modoDibujado = DIFERIDO;

	bool cuboActivo = false;
	bool tetraedroActivo = false; 
	bool plyActivo = false; 
	bool revActivo = false; 
	bool cilActivo = false; 
	bool conActivo = false; 
	bool sphActivo = false; 

	bool ejesActivo = false;

	bool luzActiva;
	bool luzPActiva = true;
	bool luzDActiva = false;

	bool tapas = true;
	bool suavizado = true;

	bool animacionActiva = false;
	float velocidadAnimacion = 0.01;
	
	angulo angle = NINGUNO;
	camara estadoRaton;

	std::map<patron,GLenum> polygonMode;

	// Objetos de la escena
	Ejes ejes;
	Cubo * cubo = nullptr ;
	Tetraedro * tetraedro= nullptr ; 
	ObjPLY* ply = nullptr;
	ObjRevolucion* rev = nullptr;
	Cilindro* cil = nullptr;
	Cono* con = nullptr;
	Esfera* sph = nullptr;

	Cuadro* cuadro = nullptr;
	Skysphere* sky = nullptr;

	LuzPosicional* luzP = nullptr;
	LuzDireccional* luzD = nullptr;

	Morsmanum* mors = nullptr;
	int gLibertad = -1;
	std::vector<float> gValor;

	std::vector<Camara> camaras;
	unsigned camaraActiva = 0;
	float x0, y0;

public:

	Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

	void clickRaton(int boton, int estado, int x, int y);
	void ratonMovido(int x, int y);

	void animacion();

};
#endif
