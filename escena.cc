#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

void Escena::inicializar_objsRevolucion() 
{
  delete rev;
  rev = new ObjRevolucion("./plys/peon.ply", 50, tapaSup, tapaInf);
  delete cil;
  cil = new Cilindro(2, 50, 70, 50, tapaSup, tapaInf);
  delete con;
  con = new Cono(20, 50, 70, 50, tapaSup, tapaInf);
  delete sph;
  sph = new Esfera(20, 50, 60, tapaSup, tapaInf);
}

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );
    cubo = new Cubo(70);
    tetraedro = new Tetraedro();
    ply = new ObjPLY("./plys/ant.ply");
    inicializar_objsRevolucion();

    luz = new LuzPosicional(Tupla3f(0, -10, 100), GL_LIGHT0); //temporal
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
  glEnable(GL_CULL_FACE);
  glEnable(GL_NORMALIZE);
  glPointSize(3);
  polygonMode.insert(std::pair<patron, GLenum>(SOLIDO, GL_FILL));
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
  ejes.draw();

  for (auto i : polygonMode) {
    glPolygonMode(GL_FRONT, i.second);
    if (cuboActivo) {
      glPushMatrix();
        glTranslatef(100, 0, -100);
        cubo->draw(modoDibujado, i.first);
      glPopMatrix();
    }
    if (tetraedroActivo) {
      glPushMatrix();
        glTranslatef(0, 0, -100);
        tetraedro->draw(modoDibujado, i.first);
      glPopMatrix();
    }
    if (plyActivo) {
      glPushMatrix();
        glTranslatef(-110, 0, -100);
        glScalef(4,4,4);
        ply->draw(modoDibujado, i.first);
      glPopMatrix();
    }
    if (revActivo) {
      glPushMatrix();
        glTranslatef(-110, 110, -100);
        glScalef(40,40,40);
        rev->draw(modoDibujado, i.first);
      glPopMatrix();
    }
    if (cilActivo) {
      glPushMatrix();
        glTranslatef(0, 100, -100);
        cil->draw(modoDibujado, i.first);
      glPopMatrix();
    }
    if (conActivo) {
      glPushMatrix();
        glTranslatef(110, 100, -100);
        con->draw(modoDibujado, i.first);
      glPopMatrix();
    }
    if (sphActivo) {
      glPushMatrix();
        glTranslatef(210, 0, -60);
        sph->draw(modoDibujado, i.first);
      glPopMatrix();
    }

    luz->activar(); //temporal
  }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
  using namespace std ;
  cout << "Tecla pulsada: '" << tecla << "'" << endl;
  bool salir=false;
  switch( toupper(tecla) )
  {
    case 'Q' :
    if (modoMenu!=NADA)
      modoMenu=NADA;            
    else {
    salir=true ;
    }
    break ;
    case 'O' :
    // ESTAMOS EN MODO SELECCION DE OBJETO
      modoMenu=SELOBJETO; 
      printf("Opciones disponibles: \n'C': Cubo \n'T': Tetraedro\n'G': Objeto ply\n'H': Objeto revolución\n'J': Cilindro\n'K': Cono\n'M': Esfera\n");
      break ;
      case 'C' :
        if (modoMenu==SELOBJETO) {
          if (cuboActivo)
            cuboActivo = false;
          else
            cuboActivo = true;
        }
      break;
      case 'T' :
        if (modoMenu==SELOBJETO) {
          if (tetraedroActivo)
            tetraedroActivo = false;
          else
            tetraedroActivo = true;
        }
      break;
      case 'G' :
        if (modoMenu==SELOBJETO) {
          if (plyActivo)
            plyActivo = false;
          else
            plyActivo = true;
        }
      break;
      case 'H' :
        if (modoMenu==SELOBJETO) {
          if (revActivo)
            revActivo = false;
          else
            revActivo = true;
        }
      break;
      case 'J' :
        if (modoMenu==SELOBJETO) {
          if (cilActivo)
            cilActivo = false;
          else
            cilActivo = true;
        }
      break;
      case 'K' :
        if (modoMenu==SELOBJETO) {
          if (conActivo)
            conActivo = false;
          else
            conActivo = true;
        }
      break;
      case 'M' :
        if (modoMenu==SELOBJETO) {
          if (sphActivo)
            sphActivo = false;
          else
            sphActivo = true;
        }
      break;

    case 'V' :
    // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
      modoMenu=SELVISUALIZACION;
      printf("Opciones disponibles: \n'L': Línea \n'P': Puntos\n'S': Sólido\n'A': Ajedrez\n'Y': Ver tapa superior\n'U': Ver tapa inferior\n");
      printf("'R': Desactivar suavizado\n'I': Activar iluminación\n");
      break ;
      case 'L' :
        if (modoMenu==SELVISUALIZACION) {
          if (polygonMode.find(LINEA) == polygonMode.end()) {
            polygonMode.insert(std::pair<patron, GLenum>(LINEA,GL_LINE));
            polygonMode.erase(LUZ); 
            glDisable(GL_LIGHTING);
          }
          else
            polygonMode.erase(LINEA);
        }
      break;
      case 'P' :
        if (modoMenu==SELVISUALIZACION) {
          if (polygonMode.find(PUNTO) == polygonMode.end()) {
            polygonMode.insert(std::pair<patron, GLenum>(PUNTO,GL_POINT));
            polygonMode.erase(LUZ); 
            glDisable(GL_LIGHTING);
          }
          else
            polygonMode.erase(PUNTO);
        }
      break;
      case 'S' :
        if (modoMenu==SELVISUALIZACION) {
          if (polygonMode.find(SOLIDO) == polygonMode.end()) {
            polygonMode.insert(std::pair<patron, GLenum>(SOLIDO,GL_FILL));
            polygonMode.erase(LUZ); 
            glDisable(GL_LIGHTING);
          }
          else
            polygonMode.erase(SOLIDO);
        }
      break;
      case 'A' :
        if (modoMenu==SELVISUALIZACION) {
          if (polygonMode.find(AJEDREZ) == polygonMode.end()) {
            polygonMode.insert(std::pair<patron, GLenum>(AJEDREZ,GL_FILL));
            polygonMode.erase(LUZ); 
            glDisable(GL_LIGHTING);
          }
          else
            polygonMode.erase(AJEDREZ);
        }
      break;
      case 'Y' :
        if (modoMenu==SELVISUALIZACION) {
          if (tapaSup)
            tapaSup = false;
          else
            tapaSup = true;
          inicializar_objsRevolucion();
        }
      break;
      case 'U' :
        if (modoMenu==SELVISUALIZACION) {
          if (tapaInf)
            tapaInf = false;
          else
            tapaInf = true;
          inicializar_objsRevolucion();
        }
      break;
      case 'R' :
        if (modoMenu==SELVISUALIZACION) {
          if (suavizado) {
            suavizado = false;
            glShadeModel(GL_FLAT);
          }
          else {
            suavizado = true;
            glShadeModel(GL_SMOOTH);
          }
        }
      break;
      case 'I' :
        if (modoMenu==SELVISUALIZACION) {
          if (modoMenu==SELVISUALIZACION) {
            if (polygonMode.find(LUZ) == polygonMode.end()) {
              polygonMode.clear();
              polygonMode.insert(std::pair<patron, GLenum>(LUZ,GL_FILL));
              glEnable(GL_LIGHTING);
              printf("Opciones de iluminación: \n'0..7': Activar luz n\n'A': variación de alfa\n'B': variación de beta\n'>': incrementar ángulo\n");
              printf("'<': decrementar ángulo\n");
            }
            else {
              glDisable(GL_LIGHTING);
              polygonMode.erase(LUZ); 
            }
          }
        }
        break;

    case 'D' :
    // ESTAMOS EN MODO SELECCION DE DIBUJADO
      modoMenu=SELDIBUJADO;
      printf("Opciones disponibles: \n'1': Modo Inmediato\n'2': Modo diferido\n");
      break ;
      case '1' :
        if (modoMenu==SELDIBUJADO)
          modoDibujado = INMEDIATO;
      break;
      case '2' :
        if (modoMenu==SELDIBUJADO)
          modoDibujado = DIFERIDO;
      break;
  }
  return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
