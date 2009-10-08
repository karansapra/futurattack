/*
 * OBJ3DObject.h
 *
 *  Created on: 7 oct. 2009
 *      Author: clement
 */

#ifndef OBJ3DOBJECT_H_
#define OBJ3DOBJECT_H_

#include "I3DObject.h"
#include "Constants.h"

class OBJ3DObject: public I3DObject {
	Vertex3f _vs[OBJ_FILE_MAX_VERTEX];
	int _vcount;
	Vertex3f _vns[OBJ_FILE_MAX_NORMALS];
	int _vncount;
	Vertex2f _vts[OBJ_FILE_MAX_TEXTCOORDS];
	int _vtcount;
	Triangle _tris[OBJ_FILE_MAX_TRIANGLES];
	int _tricount;

	bool _switch;

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
