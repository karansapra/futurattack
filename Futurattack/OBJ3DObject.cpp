/*
 * OBJ3DObject.cpp
 *
 *  Created on: 7 oct. 2009
 *      Author: clement
 */

#include "OBJ3DObject.h"

OBJ3DObject::OBJ3DObject() : I3DObject() {
	_switch = false;
	for (int i=0;i<OBJ_FILE_MAX_MESHES;i++)
		_meshes[i]=NULL;
}

OBJ3DObject::~OBJ3DObject() {
	// TODO Auto-generated destructor stub
}

void OBJ3DObject::SwitchTextureOrigin()
{
	_switch = true;
}

const char *OBJ3DObject::ToString()
{
	return "OBJ3DObject";
}



void OBJ3DObject::Render()
{
	for (int i=0;i<_nmeshes;i++)
		_meshes[i]->Render();
}



bool OBJ3DObject::Load(const char *filename)
{
	_nmeshes = 0;

	int vertex_count=0;
	int normal_count=0;
	int texture_count=0;

	int vertex_list_count=0;
	int normal_list_count=0;
	int texture_list_count=0;


	char buffer_line[OBJ_FILE_LINE_LENGTH];
	int pos=0;

	int v1, v2, v3;
	int n1, n2, n3;
	int t1, t2, t3;

	FILE * f = fopen(filename,"r");

	if (f==NULL)
		return false;

	Vertex3f * vertex = new Vertex3f[OBJ_FILE_MAX_VERTEX];
	Vertex3f * vertex_list = new Vertex3f[OBJ_FILE_MAX_VERTEX*3];

	Vertex3f * normal = new Vertex3f[OBJ_FILE_MAX_NORMALS];
	Vertex3f * normal_list = new Vertex3f[OBJ_FILE_MAX_NORMALS*3];

	Vertex2f * texture = new Vertex2f[OBJ_FILE_MAX_TEXTCOORDS];
	Vertex2f * texture_list = new Vertex2f[OBJ_FILE_MAX_TEXTCOORDS*3];

	while (!feof(f))
	{
		while ((buffer_line[pos]=fgetc(f))!='\n' && !feof(f) && pos<OBJ_FILE_LINE_LENGTH-1)
			pos++;
		buffer_line[++pos]=0;
		pos = 0;

		//Une ligne est detectée
		//On regarde le premier caractere de la ligne, pour voir les donnees qui
		//arrivent
		switch (buffer_line[0])
		{
		case 'v':
			if (buffer_line[1]==' ')
			{
				//On est dans le cas d'un vertex simple, de positionnement
				sscanf(buffer_line+2,"%f %f %f",
						&vertex[vertex_count].x,
						&vertex[vertex_count].y,
						&vertex[vertex_count].z);
				vertex_count++;
			} else if (buffer_line[1]=='n')
			{
				sscanf(buffer_line+3,"%f %f %f",
						&normal[normal_count].x,
						&normal[normal_count].y,
						&normal[normal_count].z);
				printf("N:%f %f %f\n",
						normal[normal_count].x,
						normal[normal_count].y,
						normal[normal_count].z);
				normal_count++;

			} else if (buffer_line[1]=='t')
			{
				sscanf(buffer_line+3,"%f %f",
						&texture[texture_count].u,
						&texture[texture_count].v);
				if (_switch)
					texture[texture_count].v = 1.0-texture[texture_count].v;
				texture_count++;
			}
			break;

		case 'f':
			if (texture_count!=0)
			{
			//On est dans le cas d'une face
			sscanf(buffer_line+2,"%d/%d/%d %d/%d/%d %d/%d/%d",
					&v1,&t1,&n1,
					&v2,&t2,&n2,
					&v3,&t3,&n3);
			} else
			{
				sscanf(buffer_line+2,"%d//%d %d//%d %d//%d",
						&v1,&n1,
						&v2,&n2,
						&v3,&n3);
			}
			//Liste des vertex de l'objet
			memcpy(&vertex_list[vertex_list_count++],&vertex[v1-1],sizeof(Vertex3f));
			memcpy(&vertex_list[vertex_list_count++],&vertex[v2-1],sizeof(Vertex3f));
			memcpy(&vertex_list[vertex_list_count++],&vertex[v3-1],sizeof(Vertex3f));

			//Liste des normales de l'objet
			memcpy(&normal_list[normal_list_count++],&normal[n1-1],sizeof(Vertex3f));
			memcpy(&normal_list[normal_list_count++],&normal[n2-1],sizeof(Vertex3f));
			memcpy(&normal_list[normal_list_count++],&normal[n3-1],sizeof(Vertex3f));

			if (texture_count!=0)
			{
				//Liste des UV de l'objet
				memcpy(&texture_list[texture_list_count++],&texture[t1-1],sizeof(Vertex2f));
				memcpy(&texture_list[texture_list_count++],&texture[t2-1],sizeof(Vertex2f));
				memcpy(&texture_list[texture_list_count++],&texture[t3-1],sizeof(Vertex2f));
			}
			break;

		default:
			break;
		}
	}

	fclose(f);

	_meshes[0] = new Mesh();
	_meshes[0]->SetVertexList(vertex_list,vertex_list_count);
	_meshes[0]->SetNormalList(normal_list,normal_list_count);
	_meshes[0]->BuildUp();
	_nmeshes++;

	delete[] vertex;
	delete[] vertex_list;

	delete[] normal;
	delete[] normal_list;

	delete[] texture;
	delete[] texture_list;

	_vcount = vertex_list_count;

	return true;
}


