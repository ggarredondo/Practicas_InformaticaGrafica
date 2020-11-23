#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

void Malla3D::preparar_ajedrez()
{
	for (unsigned i = 0; i < v.size(); ++i) 
		cAjedrezPares.push_back({1,0,1});

	for (unsigned i = 0; i < v.size(); ++i)
		cAjedrezImpares.push_back({0,0,0});

	for (unsigned i = 0; i < f.size(); ++i) {
		if (i%2 == 0)
			f1.push_back(f[i]);
		else
			f2.push_back(f[i]);
	}
}

void Malla3D::preparar_modos()
{
	unsigned size = v.size();

	for (unsigned i = 0; i < size; ++i) {
		if (i%2 == 0)
			cSolido.push_back({1,0,0});
		else
			cSolido.push_back({0,1,0});
	}

	for (unsigned i = 0; i < size; ++i)
		cLinea.push_back({1,1,0});

	for (unsigned i = 0; i < size; ++i)
		cPunto.push_back({0,0,0});

	preparar_ajedrez();
	calcular_normales();
}

inline Tupla3f producto_vectorial(const Tupla3f& a, const Tupla3f& b) {
	return Tupla3f(a[1]*b[2]-b[1]*a[2], a[0]*b[2]-b[0]*a[2], a[0]*b[1]-b[0]*a[1]);
}

inline float modulo_vector(const Tupla3f& vector) {
	return sqrt(pow(vector[0],2)+pow(vector[1],2)+pow(vector[2],2));
}

inline Tupla3f normalizar(Tupla3f& vector) {
	return Tupla3f(vector[0]/modulo_vector(vector), vector[1]/modulo_vector(vector), vector[2]/modulo_vector(vector));
}

void Malla3D::calcular_normales()
{
	std::vector<Tupla3f> mv;
	Tupla3f a, b, mc, nc;
	std::vector<int> vertices_cara;

	//inicializamos tabla de vectores perpendiculares a los vértices
	for (unsigned i = 0; i < v.size(); ++i)
		mv.push_back(Tupla3f(0,0,0));

	for (auto i : f) {
		for (unsigned j = 0; j < 3; ++j) {
			vertices_cara.push_back(i[j]);         //se obtienen los vértices que forman la cara
			a[j] = v[i[1]][j] - v[i[0]][j];        //se calcula el vector a
			b[j] = v[i[2]][j] - v[i[0]][j];        //se calcula el vector b
		}
		mc = producto_vectorial(a, b);             //obtenemos el vector perpendicular a la cara
		nc = normalizar(mc);                       //obtenemos el vector normal de la cara

		for (auto j : vertices_cara) {             //sumamos la normal de la cara para el vértice
			mv[j][0] += nc[0];
			mv[j][1] += nc[1];
			mv[j][2] += nc[2];             
		}
	}

	//normalizamos mv para cada vértice y lo introducimos en nv
	for (auto i : mv)
		nv.push_back(normalizar(i));
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(std::vector<Tupla3f>& c, std::vector<Tupla3i>& f0)
{
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, c.data());
	glEnableClientState(GL_VERTEX_ARRAY);

	//indicar el formato y la dirección de memoria del array de vértices
	//(son tuplas de 3 valores float, sin espacio entre ellas)
	glVertexPointer(3, GL_FLOAT, 0, v.data());

	//visualizar, indicando: tipo de primitva, número de índices,
	//tipo de los índices, y dirección de la tabla de índices
	glDrawElements(GL_TRIANGLES, f0.size()*3, GL_UNSIGNED_INT, f0.data());

	//deshabilitar array de vértices
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

GLuint Malla3D::CrearVBO (GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid* puntero_ram)
{
	GLuint id_vbo; //identificador de VBO
	glGenBuffers(1, &id_vbo); //crear nuevo VBO, obtener identificador
	glBindBuffer(tipo_vbo, id_vbo); //activar el VBO usando su identificador

	glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW); //transferencia de datos desde RAM a GPU

	glBindBuffer(tipo_vbo, 0); //desactivación del VBO (activar 0)
	return id_vbo; //devolver el identificador resultado
}

void Malla3D::draw_ModoDiferido(GLuint& id_vbo_c, GLuint& id_vbo_tr, std::vector<Tupla3f>& c, std::vector<Tupla3i>& f0)
{
	//Se verifica si los identificadores de VBO son 0, y, si lo son, se invoca a CrearVBO para cada tabla
	if (id_vbo_ver == 0) 
		id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
	if (id_vbo_tr == 0)
		id_vbo_tr = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f0.size()*3*sizeof(int), f0.data());
	if (id_vbo_c == 0)
		id_vbo_c = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, c.size()*3*sizeof(float), c.data());

	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c);
	glColorPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_COLOR_ARRAY);

	//especificar localización y formato de la tabla de vertices, habilitar tabla

	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); //activar VBO de vértcies
	glVertexPointer(3, GL_FLOAT, 0, 0); //especifica formato y offset (=0)
	glBindBuffer(GL_ARRAY_BUFFER, 0); //desactiva VBO de vértices
	glEnableClientState(GL_VERTEX_ARRAY); //habilitar tabla de vértices

	//visualizar triángulos con glDrawElements (puntero a tabla == 0)

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tr); //activar VBO de triángulos
	glDrawElements(GL_TRIANGLES, 3*f0.size(), GL_UNSIGNED_INT, 0); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //desactivar VBO de triángulos

	//desactivar uso de array de vértices

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(dibujado d, patron p)
{
	m.aplicar();
	switch(d)
	{
		case INMEDIATO:
			switch (p) {
				case SOLIDO:
					draw_ModoInmediato(cSolido, f);
					break;
				case AJEDREZ:
					draw_ModoInmediato(cAjedrezPares, f1);
					draw_ModoInmediato(cAjedrezImpares, f2);
					break;
				case LINEA:
					draw_ModoInmediato(cLinea, f);
					break;
				case PUNTO:
					draw_ModoInmediato(cPunto, f);
					break;	
			}
			break;
		case DIFERIDO:	
			switch (p) {
				case SOLIDO:
					draw_ModoDiferido(id_vbo_cSolido, id_vbo_tri, cSolido, f);
					break;
				case AJEDREZ:
					draw_ModoDiferido(id_vbo_cAjedrezPares, id_vbo_tri1, cAjedrezPares, f1);
					draw_ModoDiferido(id_vbo_cAjedrezImpares, id_vbo_tri2, cAjedrezImpares, f2);
					break;
				case LINEA:
					draw_ModoDiferido(id_vbo_cLinea, id_vbo_tri, cLinea, f);
					break;
				case PUNTO:
					draw_ModoDiferido(id_vbo_cPunto, id_vbo_tri, cPunto, f);
					break;	
			}
			break;
	}
}
