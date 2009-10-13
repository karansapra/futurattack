/*
 * Mesh.h
 *
 *  Created on: 8 oct. 2009
 *      Author: clement
 */

#ifndef MESH_H_
#define MESH_H_

//Pour utiliser OpenGL 1.5, etc...
#define GL_GLEXT_PROTOTYPES

#include <GL/freeglut.h>
#include <GL/glx.h>
#include <GL/glext.h>

#include "IRenderable.h"
#include "I3DObject.h"
#include "IMaterial.h"
#include "Constants.h"


#define VERTEX_DATA 		0
#define NORMAL_DATA	 		1
#define TEXTURE_DATA	 	2

class Mesh: public IRenderable {
	GLuint _vbo[3];
	bool _already_built;
	bool _normal;
	bool _vertex;
	bool _texcoord;
	int _n;
	char _mesh_name[MAX_MESH_NAME_LENGTH];

	IMaterial * _material;

	Vertex3f * _vertex_list;
	Vertex3f * _normal_list;
	Vertex2f * _texcoord_list;

public:
	Mesh();

	/*
	 * Construit un mesh vide, en lui ajoutant un nom que le logiciel 3D
	 * a pu lui donner
	 */
	Mesh(const char *name);

	/*
	 * Détruit et désalloue tout pour le mesh
	 */
	virtual ~Mesh();

	/*
	 * Fixe les point a transferer dans la CG
	 */
	void SetVertexList(Vertex3f * vertex_list, int n);

	/*
	 * Fixe les normales a envoyer dans la CG
	 */
	void SetNormalList(Vertex3f * normal_list, int n);

	/*
	 * Fixe les coordonnées textures a envoyer dans la CG
	 */
	void SetTexCoordList(Vertex2f * texcoord_list, int n);

	/*
	 * Permet de definir le materiau, et de specifier si on supprime l'ancien
	 */
	void SetMaterial(IMaterial * material, bool delete_last=true);

	/*
	 *	Permet d'assembler le mesh, c'est a dire transferer ses données
	 *	intrinsèques (vertices, normales, texcoords) a la CG via les Buffer
	 *	Objects
	 */
	void BuildUp();

	/*
	 * Effectue le rendu du mesh en se servant des VBO
	 */
	void Render();

	/*
	 * Renvoie le nom de la classe
	 */
	const char * ToString();
};

#endif /* MESH_H_ */
