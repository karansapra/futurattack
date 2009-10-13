/*
 * OBJ3DObject.h
 *
 *  Created on: 7 oct. 2009
 *      Author: clement
 */

#ifndef OBJ3DOBJECT_H_
#define OBJ3DOBJECT_H_

//Pour utiliser OpenGL 1.5, etc...
#define GL_GLEXT_PROTOTYPES

#include <GL/freeglut.h>
#include <GL/glx.h>
#include <GL/glext.h>

#include "I3DObject.h"
#include "IMaterial.h"
#include "StandardMaterial.h"
#include "Constants.h"
#include "Mesh.h"


class OBJ3DObject: public I3DObject {
	int _vcount;

	bool _switch;

	Mesh * _meshes[OBJ_FILE_MAX_MESHES];
	int _nmeshes;

	IMaterial * _parsed_materials[OBJ_FILE_MAX_MATERIALS];
	int _nparsed_materials;
	void _parse_mtl_file(char * file);

public:
	OBJ3DObject();
	virtual ~OBJ3DObject();

	bool Load(const char * filename);

	//Blender pose l'origine de la texture en bas a gauche, donc pr activer le mode
	void SwitchTextureOrigin();

	void Render();

	const char * ToString();
};

#endif /* OBJ3DOBJECT_H_ */
