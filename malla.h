// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************
typedef enum {SOLIDO, AJEDREZ, LINEA, PUNTO, LUZ} patron;
typedef enum {INMEDIATO, DIFERIDO} dibujado;

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(std::vector<Tupla3f>& c, std::vector<Tupla3i>& f0, GLuint tam);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(GLuint& id_vbo_c, GLuint& id_vbo_tr, std::vector<Tupla3f>& c, std::vector<Tupla3i>& f0, GLuint tam);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(dibujado d, patron p);

   inline void setMaterial(const Material& mat) {
      m = mat;
   }

   protected:

   GLuint tam1, tamA, tamB;

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   void preparar_modos();
   void preparar_ajedrez();

   GLuint CrearVBO (GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid* puntero_ram);

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3f> nv ; // vector de normales de vértices
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo

   Textura *textura = nullptr;
   std::vector<Tupla2f> ct; // tablas de coordenadas de textura

   std::vector<Tupla3i> f1;
   std::vector<Tupla3i> f2;

   std::vector<Tupla3f> cSolido;
   std::vector<Tupla3f> cAjedrezPares;
   std::vector<Tupla3f> cAjedrezImpares;
   std::vector<Tupla3f> cLinea;
   std::vector<Tupla3f> cPunto;

   Material m;

   GLuint id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_tri1 = 0, id_vbo_tri2 = 0,
   id_vbo_cSolido = 0, id_vbo_cAjedrezPares = 0, id_vbo_cAjedrezImpares = 0,
   id_vbo_cLinea = 0, id_vbo_cPunto = 0, id_vbo_normales = 0, id_vbo_textura = 0;

} ;


#endif
