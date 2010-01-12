#ifndef OBJFILELOADER_H
#define OBJFILELOADER_H

#include "types.h"
#include "core.h"

bool LoadObjFile(U8 * model_file, VertexArray & varray);
bool LoadObjFile(U8 * model_file, Mesh & mesh);

#endif