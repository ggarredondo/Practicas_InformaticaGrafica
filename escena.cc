#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

void Escena::actualizarTapas()
{
  rev->actualizarTapas(tapas);
  cil->actualizarTapas(tapas);
  con->actualizarTapas(tapas);
  sph->actualizarTapas(tapas);
}

void Escena::pose_idle()
{
  mors->rotarCabeza(30,0,0);
  mors->rotarTorso(30,0,0);
  mors->abrirFauces(0);
  mors->inclinarCabezaSuperior(0);

  mors->trasladarTorsoAislado(0);
  mors->rotarTorsoAislado(0);

  mors->rotarBrazoIzq(-25,-60,-70);
  mors->rotarBrazoDech(-25,60,70);

  mors->rotarPiernaIzq(-60,0,10);
  mors->rotarRodillaIzq(40,-30,0);
  mors->rotarTalonIzq(-10,0,0);

  mors->rotarPiernaDech(-60,0,-10);
  mors->rotarRodillaDech(40,30,0);
  mors->rotarTalonDech(-10,0,0);

  gValor = {0,0,0};
}

void Escena::animacion() 
{
  float t = velocidadAnimacion*glutGet(GLUT_ELAPSED_TIME);

  if (animacionActiva) {
    mors->rotarCabeza(30-sin(t*0.5)*4,0,0);
    mors->abrirFauces(abs(sin(t)*1.5));
    mors->inclinarCabezaSuperior(sin(t)*2.5);

    mors->trasladarTorsoAislado(sin(t*0.5)*0.05);
    mors->rotarTorsoAislado(sin(t*0.5)*0.2);

    mors->rotarBrazoIzq(-25+cos(t*0.5)*0.5,-60,-70+sin(t*0.5)*0.5);
    mors->rotarBrazoDech(-25+sin(t*0.5)*0.5,60,70+sin(t*0.5)*0.5);

    mors->rotarPiernaIzq(-60+sin(t*0.5)*0.75,0,10);
    mors->rotarRodillaIzq(40-sin(t*0.5)*0.75,-30,0);
    mors->rotarTalonIzq(-10-sin(t*0.5)*0.75,0,0);

    mors->rotarPiernaDech(-60+sin(t*0.5)*0.75,0,-10);
    mors->rotarRodillaDech(40-sin(t*0.5)*0.75,30,0);
    mors->rotarTalonDech(-10-sin(t*0.5)*0.75,0,0);

    luzP->trasladarLuz(cos(t*0.1)*1000,1000,-sin(t*0.1)*1000);
  }
}

Escena::Escena()
{
  Front_plane       = 50.0;
  Back_plane        = 2000.0;
  Observer_distance = 4*Front_plane;

  ejes.changeAxisSize( 5000 );
  cubo = new Cubo(70);
  tetraedro = new Tetraedro();
  ply = new ObjPLY("./plys/ant.ply");

  rev = new ObjRevolucion("./plys/peon.ply", 50, tapas);
  cil = new Cilindro(2, 50, 70, 50, tapas);
  con = new Cono(20, 50, 70, 50, tapas);
  sph = new Esfera(20, 50, 60, tapas);
  rev->setMaterial(Material(Tupla4f(0,0,0,0),Tupla4f(0,0,1,0),Tupla4f(0,0,0,0), 10));
  cil->setMaterial(Material(Tupla4f(0,0,0,0),Tupla4f(0,0,0,0),Tupla4f(0,1,0,0), 50));

  cuadro = new Cuadro();
  sky = new Skysphere(1000,50,1500,"./texturas/nightsky.jpg");
  sky->setMaterial(Material(Tupla4f(0,0,0,0),Tupla4f(0,0,0,0),Tupla4f(1,1,1,1), 1));

  mors = new Morsmanum();
  pose_idle();
  
  luzP = new LuzPosicional(Tupla3f(-50,0,100), GL_LIGHT0, Tupla4f(0.8,0.8,1,0.8), Tupla4f(0.8,0.8,1,0.8), Tupla4f(0.8,0.8,1,0.8));
  luzD = new LuzDireccional(Tupla2f(0,0), GL_LIGHT1, Tupla4f(0.8,0.8,1,0.8), Tupla4f(0.8,0.8,1,0.8), Tupla4f(0.8,0.8,1,0.8));

  polygonMode.insert(std::pair<patron, GLenum>(LUZ, GL_FILL));
  camaras.push_back(Camara({0,0,Observer_distance},{0,0,0},{0,1,0},0,0,0,0,0,0,PERSPECTIVA));
  camaras.push_back(Camara({0,0,Observer_distance},{0,0,0},{0,1,0},0,0,0,0,0,0,ORTOGONAL));
  camaras.push_back(Camara({Observer_distance,0,0},{0,0,0},{0,1,0},0,0,0,0,0,0,PERSPECTIVA));
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
  glClearColor( 0.0, 0.0, 0.0, 0.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

  glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

  Width  = UI_window_width/10;
  Height = UI_window_height/10;

  change_projection( float(UI_window_width)/float(UI_window_height) );
  glViewport( 0, 0, UI_window_width, UI_window_height );
  glEnable(GL_CULL_FACE);
  glEnable(GL_NORMALIZE);
  glPointSize(3);
  glEnable(GL_LIGHTING);
  
  printf("Opciones disponibles: \n'O': Selección de objeto\n'V': Selección de modo de visualización\n'D': Selección de modo de dibujado\n");
  printf("'A': Activar animación automática\n'M': Animación manual\n'C': Selección de cámara\n'Q': Salir del programa\n");
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
  glMatrixMode(GL_MODELVIEW);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();

  luzActiva = polygonMode.find(LUZ) != polygonMode.end();
  if (ejesActivo) {
    if (luzActiva)
      glDisable(GL_LIGHTING);
    ejes.draw();
    if (luzActiva)
      glEnable(GL_LIGHTING);
  }

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
        glTranslatef(0, 0, -130);
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

    mors->draw(modoDibujado, i.first);
    cuadro->draw(modoDibujado, i.first);

    glPushMatrix();
      glTranslatef(0,-150,0);
      sky->draw(modoDibujado, i.first);
    glPopMatrix();
  }
  if (luzPActiva)
    luzP->activar();
  if (luzDActiva)
    luzD->activar();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

void Escena::cambiarCamara(unsigned index) {
  camaras[index] = camaras[camaraActiva];
  camaraActiva = index;
  camaras[index].setProyeccion();
}

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
  using namespace std ;
  cout << "Tecla pulsada: '" << tecla << "'" << endl;
  bool salir=false;
  switch( toupper(tecla) )
  {
    case 'Q' :
      if (modoMenu != NADA) {
        modoMenu = NADA;   
        printf("Opciones disponibles: \n'O': Selección de objeto\n'V': Selección de modo de visualización\n'D': Selección de modo de dibujado\n");
        printf("'A': Activar animación automática\n'M': Animación manual\n'C': Selección de cámara\n'Q': Salir del programa\n");      
      }
      else 
        salir = true;
    break ;

    case 'O' :
    // ESTAMOS EN MODO SELECCION DE OBJETO
      modoMenu = SELOBJETO; 
      printf("Opciones disponibles: \n'C': Cubo \n'T': Tetraedro\n'G': Objeto ply\n'H': Objeto revolución\n'J': Cilindro\n'K': Cono\n'L': Esfera\n");
      printf("'E': Ejes\n");
    break;

    case 'E' :
      if (modoMenu == SELOBJETO) {
        if (ejesActivo)
          ejesActivo = false;
        else
          ejesActivo = true;
      }
    break;

    case 'V' :
    // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
      modoMenu = SELVISUALIZACION;
      printf("Opciones disponibles: \n'L': Línea \n'P': Puntos\n'S': Sólido\n'A': Ajedrez\n'T': Activar tapas\n");
      printf("'R': Desactivar suavizado\n'I': Activar iluminación\n");
    break;

    case 'D' :
    // ESTAMOS EN MODO SELECCION DE DIBUJADO
      modoMenu = SELDIBUJADO;
      printf("Opciones disponibles: \n'1': Modo Inmediato\n'2': Modo diferido\n");
      break;

    case '1' :
      if (modoMenu == SELDIBUJADO) {
        printf("Modo inmediato\n");
        modoDibujado = INMEDIATO;
      }
      else if (luzActiva && modoMenu == SELVISUALIZACION) {
        if (luzPActiva) {
          luzPActiva = false;
          luzP->desactivar();
        }
        else {
          luzPActiva = true;
          dibujar();
        }
      }
      else if (modoMenu == MANUAL)
        gLibertad = 1;
      else if (modoMenu == CAMARA)
        cambiarCamara(0);
    break;

    case '2' :
      if (modoMenu == SELDIBUJADO) {
        printf("Modo diferido\n");
        modoDibujado = DIFERIDO;
      }
      else if (luzActiva && modoMenu == SELVISUALIZACION) {
        if (luzDActiva) {
          luzDActiva = false;
          luzD->desactivar();
        }
        else {
          luzDActiva = true;
          dibujar();
        }
      }
      else if (modoMenu == MANUAL)
        gLibertad = 2;
      else if (modoMenu == CAMARA)
        cambiarCamara(1);
    break;

    case '3' :
      if (modoMenu == MANUAL)
        gLibertad = 3;
      else if (modoMenu == CAMARA)
        cambiarCamara(2);
    break;

    case ',' :
      if (modoMenu == CAMARA) {
        camaras[camaraActiva].zoom(-1);
        camaras[camaraActiva].setProyeccion();
      }
    break;

     case '.' :
      if (modoMenu == CAMARA) {
        camaras[camaraActiva].zoom(1);
        camaras[camaraActiva].setProyeccion();
      }
    break;

    case 'C' :
      if (modoMenu == SELOBJETO) {
        if (cuboActivo)
          cuboActivo = false;
        else
          cuboActivo = true;
      }
      else {
        modoMenu = CAMARA;
        printf("Opciones disponibles: \n'1-3': Seleccionar cámara\n',': Zoom out\n'.': Zoom in\n");
      }
    break;

    case 'T' :
      if (modoMenu == SELOBJETO) {
        if (tetraedroActivo)
          tetraedroActivo = false;
        else
          tetraedroActivo = true;
      }
      else if (modoMenu==SELVISUALIZACION) {
        if (tapas) {
          tapas = false;
          actualizarTapas();
        }
        else {
          tapas = true;
          actualizarTapas();
        }
      }
    break;

    case 'G' :
      if (modoMenu == SELOBJETO) {
        if (plyActivo)
          plyActivo = false;
        else
          plyActivo = true;
      }
    break;

    case 'H' :
      if (modoMenu == SELOBJETO) {
        if (revActivo)
          revActivo = false;
        else
          revActivo = true;
      }
    break;

    case 'J' :
      if (modoMenu == SELOBJETO) {
        if (cilActivo)
          cilActivo = false;
        else
          cilActivo = true;
      }
    break;

    case 'K' :
      if (modoMenu == SELOBJETO) {
        if (conActivo)
          conActivo = false;
        else
          conActivo = true;
      }
    break;

    case 'L' :
      if (modoMenu == SELOBJETO) {
        if (sphActivo)
          sphActivo = false;
        else
          sphActivo = true;
      }
      else if (modoMenu==SELVISUALIZACION) {
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
        if (polygonMode.find(PUNTO) == polygonMode.end())
          polygonMode.insert(std::pair<patron, GLenum>(PUNTO,GL_POINT));
        else
          polygonMode.erase(PUNTO);
      }
    break;

    case 'S' :
      if (modoMenu==SELVISUALIZACION) {
        if (polygonMode.find(SOLIDO) == polygonMode.end()) {
          polygonMode.insert(std::pair<patron, GLenum>(SOLIDO,GL_FILL));
          polygonMode.erase(LUZ); 
          polygonMode.erase(AJEDREZ);
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
          polygonMode.erase(SOLIDO); 
          glDisable(GL_LIGHTING);
        }
        else
          polygonMode.erase(AJEDREZ);
      }
      else {
        modoMenu = ANIM;
        if (animacionActiva) {
          animacionActiva = false;
          pose_idle();
          luzP->trasladarLuz(-50,0,100);
        }
        else {
          printf("Opciones disponibles: \n'+': Acelerar animación\n'-': Decelerar animación\n");
          animacionActiva = true;
        }
      }
    break;

    case '+' :
      if (animacionActiva && modoMenu == ANIM) {
        velocidadAnimacion += 0.001;
        std::cout << velocidadAnimacion << std::endl;
      }
      else if (modoMenu == MANUAL) {
        switch (gLibertad) {
          case 1 :
            gValor[0] += 0.5;
            mors->abrirFauces(gValor[0]);
          break;
          case 2 :
            gValor[1] += 0.5;
            mors->inclinarCabezaSuperior(gValor[1]);
          break;
          case 3 :
            gValor[2] += 0.5;
            mors->rotarCabeza(30+gValor[2],0,0);
          break;
        }
      }
    break;
    
    case '-' :
      if (animacionActiva && modoMenu == ANIM && velocidadAnimacion > 0) {
        velocidadAnimacion -= 0.001;
        std::cout << velocidadAnimacion << std::endl;
      }
      else if (modoMenu == MANUAL) {
        switch (gLibertad) {
          case 1 :
            gValor[0] -= 0.5;
            mors->abrirFauces(gValor[0]);
          break;
          case 2 :
            gValor[1] -= 0.5;
            mors->inclinarCabezaSuperior(gValor[1]);
          break;
          case 3 :
            gValor[2] -= 0.5;
            mors->rotarCabeza(30+gValor[2],0,0);
          break;
        }
      }
    break;

    case 'M' :
      modoMenu = MANUAL;
      if (animacionActiva) {
        animacionActiva = false;
        pose_idle();
        luzP->trasladarLuz(-50,0,100);
      }
      printf("Opciones disponibles: \n'1': Fauces\n'2': Rotación cabeza superior\n'3': Rotación cabeza completa\n");
      printf("'+': Aumentar valor\n'-': Disminuir valor\n");
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
        if (polygonMode.find(LUZ) == polygonMode.end()) {
          polygonMode.erase(SOLIDO);
          polygonMode.erase(AJEDREZ);
          polygonMode.erase(LINEA);
          polygonMode.insert(std::pair<patron, GLenum>(LUZ,GL_FILL));
          glEnable(GL_LIGHTING);
          printf("Opciones de iluminación: \n'1-2': Activar luz n\n'X': variación de alfa\n'B': variación de beta\n'>': incrementar ángulo\n");
          printf("'<': decrementar ángulo\n");
        }
        else {
          glDisable(GL_LIGHTING);
          polygonMode.erase(LUZ); 
        }
      }
    break;

    case 'X' :
      if (luzActiva && modoMenu == SELVISUALIZACION)
        angle = ALFA;
    break;

    case 'B' :
      if (luzActiva && modoMenu == SELVISUALIZACION)
        angle = BETA;
    break;

    case '>' :
      if (luzActiva && modoMenu == SELVISUALIZACION) {
        if (angle == ALFA)
          luzD->variarAnguloAlpha(0.1);
        else if (angle == BETA)
          luzD->variarAnguloBeta(0.1);
      }
    break;

    case '<' :
      if (luzActiva && modoMenu == SELVISUALIZACION) {
        if (angle == ALFA)
          luzD->variarAnguloAlpha(-0.1);
        else if (angle == BETA)
          luzD->variarAnguloBeta(-0.1);
      }
    break;
  }
  return salir;
}

void Escena::clickRaton(int boton, int estado, int x, int y)
{
  if (boton == GLUT_RIGHT_BUTTON) {
    if (estado == GLUT_DOWN) {
      x0 = x;
      y0 = y;
      estadoRaton = FIRSTPERSON;
    }
    else
      estadoRaton = EXAMINAR;
  }
}

void Escena::ratonMovido(int x, int y)
{
  if (estadoRaton == FIRSTPERSON) {
    camaras[camaraActiva].girar((x - x0)*0.5, (y - y0)*0.5);
    x0 = x;
    y0 = y;
  }
}

//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
  switch ( Tecla1 )
  {
   case GLUT_KEY_LEFT:
      camaras[camaraActiva].rotarYExaminar(-0.1);
      break;
   case GLUT_KEY_RIGHT:
      camaras[camaraActiva].rotarYExaminar(0.1);
      break;
   case GLUT_KEY_UP:
      camaras[camaraActiva].rotarVerticalExaminar(-0.1);
      break;
   case GLUT_KEY_DOWN:
      camaras[camaraActiva].rotarVerticalExaminar(0.1);
      break;
   case GLUT_KEY_PAGE_UP:
      Observer_distance *= 1.2 ;
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
  const float wx = float(Height)*ratio_xy ;
  for (auto& i : camaras)
    i.modificarVisualizacion( -wx, wx, -Height, Height, Front_plane, Back_plane );
  camaras[camaraActiva].setProyeccion();
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
  camaras[camaraActiva].setObserver();
}
