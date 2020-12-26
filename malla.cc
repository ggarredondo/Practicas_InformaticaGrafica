#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

void Malla3D::preparar_ajedrez()
{
	for (unsigned i = 0; i < v.size(); ++i) {
		cAjedrezPares.push_back({1,0,1});
		cAjedrezImpares.push_back({0,0,0});
	}

	for (unsigned i = 0; i < tam1; ++i) {
		if (i%2 == 0)
			f1.push_back(f[i]);
		else
			f2.push_back(f[i]);
	}
}

void Malla3D::preparar_modos()
{
	tam1 = f.size();
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
	tamA = f1.size();
	tamB = f2.size();

	calcular_normales();
}

void Malla3D::calcular_normales()
{
	nv.resize(v.size(), Tupla3f(0, 0, 0));
	Tupla3f a, b, nc;

	for (auto cara : f) 
	{
		a = v[cara[1]] - v[cara[0]];
		b = v[cara[2]] - v[cara[0]];
		nc = a.cross(b);

		for (unsigned i = 0; i < 3; ++i)
			nv[cara[i]] = nv[cara[i]] + nc;
	}

	for (auto n : nv)
		n = n.normalized();
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(std::vector<Tupla3f>& c, std::vector<Tupla3i>& f0, GLuint tam)
{
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, c.data());
	glEnableClientState(GL_VERTEX_ARRAY);

	//indicar el formato y la dirección de memoria del array de vértices
	//(son tuplas de 3 valores float, sin espacio entre ellas)
	glVertexPointer(3, GL_FLOAT, 0, v.data());

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, nv.data());

	//visualizar, indicando: tipo de primitva, número de índices,
	//tipo de los índices, y dirección de la tabla de índices
	glDrawElements(GL_TRIANGLES, tam*3, GL_UNSIGNED_INT, f0.data());

	//deshabilitar array de vértices
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisableClientState(GL_COLOR_ARRAY);

	glDisableClientState(GL_NORMAL_ARRAY);
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

void Malla3D::draw_ModoDiferido(GLuint& id_vbo_c, GLuint& id_vbo_tr, std::vector<Tupla3f>& c, std::vector<Tupla3i>& f0, GLuint tam)
{
	//Se verifica si los identificadores de VBO son 0, y, si lo son, se invoca a CrearVBO para cada tabla
	if (id_vbo_ver == 0) 
		id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
	if (id_vbo_tr == 0)
		id_vbo_tr = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, tam*3*sizeof(int), f0.data());
	if (id_vbo_c == 0)
		id_vbo_c = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, c.size()*3*sizeof(float), c.data());
	if (id_vbo_normales == 0)
		id_vbo_normales = CrearVBO(GL_ARRAY_BUFFER, nv.size()*3*sizeof(float), nv.data());

	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c);
	glColorPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_COLOR_ARRAY);

	//especificar localización y formato de la tabla de vertices, habilitar tabla

	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); //activar VBO de vértcies
	glVertexPointer(3, GL_FLOAT, 0, 0); //especifica formato y offset (=0)
	glBindBuffer(GL_ARRAY_BUFFER, 0); //desactiva VBO de vértices
	glEnableClientState(GL_VERTEX_ARRAY); //habilitar tabla de vértices

	//dibujar normales
	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_normales);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//visualizar triángulos con glDrawElements (puntero a tabla == 0)

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tr); //activar VBO de triángulos
	glDrawElements(GL_TRIANGLES, 3*tam, GL_UNSIGNED_INT, 0); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //desactivar VBO de triángulos

	//desactivar uso de array de vértices

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
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
				case LUZ:
				case SOLIDO:
					draw_ModoInmediato(cSolido, f, tam1);
					break;
				case AJEDREZ:
					draw_ModoInmediato(cAjedrezPares, f1, tamA);
					draw_ModoInmediato(cAjedrezImpares, f2, tamB);
					break;
				case LINEA:
					draw_ModoInmediato(cLinea, f, tam1);
					break;
				case PUNTO:
					draw_ModoInmediato(cPunto, f, tam1);
					break;	
			}
			break;
		case DIFERIDO:	
			switch (p) {
				case LUZ:
				case SOLIDO:
					draw_ModoDiferido(id_vbo_cSolido, id_vbo_tri, cSolido, f, tam1);
					break;
				case AJEDREZ:
					draw_ModoDiferido(id_vbo_cAjedrezPares, id_vbo_tri1, cAjedrezPares, f1, tamA);
					draw_ModoDiferido(id_vbo_cAjedrezImpares, id_vbo_tri2, cAjedrezImpares, f2, tamB);
					break;
				case LINEA:
					draw_ModoDiferido(id_vbo_cLinea, id_vbo_tri, cLinea, f, tam1);
					break;
				case PUNTO:
					draw_ModoDiferido(id_vbo_cPunto, id_vbo_tri, cPunto, f, tam1);
					break;	
			}
			break;
	}
}
