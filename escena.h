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

#include "morsmanum.h" //temporal

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
typedef enum {NINGUNO, ALFA, BETA} angulo;
class Escena
{

   private:
 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

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

   bool cuboActivo = false; //C
   bool tetraedroActivo = false; //T
   bool plyActivo = false; //G
   bool revActivo = false; //H
   bool cilActivo = false; //J
   bool conActivo = false; //K
   bool sphActivo = false; //M

   bool luzActiva = true;
   bool luzPActiva = false;
   bool luzDActiva = true;

   bool tapas = true;
   bool suavizado = true;

   bool animacionActiva = false;
   float velocidadAnimacion = 0.01;

   angulo angle = NINGUNO;

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

   LuzPosicional* luzP = nullptr;
   LuzDireccional* luzD = nullptr;

   Morsmanum* mors = nullptr;
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

	void animarModeloJerarquico();

};
#endif
