/*
 * OBJ3DObject.cpp
 *
 *  Created on: 7 oct. 2009
 *      Author: clement
 */

#include "OBJ3DObject.h"

OBJ3DObject::OBJ3DObject() : I3DObject() {
	_switch = false;
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
	int v_idx;
	int n_idx;
	int t_idx;

	if (_switch)
	{
		glBegin(GL_TRIANGLES);
		for (int i=0;i<_tricount;i++)
		{
			for (int j=0;j<3;j++)
			{
				v_idx = _tris[i].vertex_indices[j]-1;
				n_idx = _tris[i].normal_indices[j]-1;
				t_idx = _tris[i].uv_indices[j]-1;
				glNormal3f(_vns[n_idx].x,_vns[n_idx].y,_vns[n_idx].z);
				glTexCoord2f(_vts[t_idx].u,1.0-_vts[t_idx].v);
				glVertex3f(_vs[v_idx].x,_vs[v_idx].y,_vs[v_idx].z);
			}
		}
		glEnd();
	} else {
		glBegin(GL_TRIANGLES);
		for (int i=0;i<_tricount;i++)
		{
			for (int j=0;j<3;j++)
			{
				v_idx = _tris[i].vertex_indices[j]-1;
				n_idx = _tris[i].normal_indices[j]-1;
				t_idx = _tris[i].uv_indices[j]-1;
				glNormal3f(_vns[n_idx].x,_vns[n_idx].y,_vns[n_idx].z);
				glTexCoord2f(_vts[t_idx].u,_vts[t_idx].v);
				glVertex3f(_vs[v_idx].x,_vs[v_idx].y,_vs[v_idx].z);
			}
		}
		glEnd();
	}
}



bool OBJ3DObject::Load(const char *filename)
{
	_vcount=0;
	_vncount=0;
	_vtcount=0;
	_tricount=0;

	char buffer_line[OBJ_FILE_LINE_LENGTH];
	int pos=0;

	FILE * f = fopen(filename,"r");
	if (f==NULL)
		return false;


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
				sscanf(buffer_line+2,"%f %f %f",&_vs[_vcount].x,&_vs[_vcount].y,&_vs[_vcount].z);
				_vcount++;
			} else if (buffer_line[1]=='n')
			{
				//On est dans le cas des normales
				sscanf(buffer_line+3,"%f %f %f",&_vns[_vncount].x,&_vns[_vncount].y,&_vns[_vncount].z);
				_vncount++;
			} else if (buffer_line[1]=='t')
			{
				//On est dans le cas des uv coords
				sscanf(buffer_line+3,"%f %f",&_vts[_vtcount].u,&_vts[_vtcount].v);
				_vtcount++;
			}
			break;

		case 'f':
			//On est dans le cas d'une face
			sscanf(buffer_line+2,"%d/%d/%d %d/%d/%d %d/%d/%d",
					&_tris[_tricount].vertex_indices[0],&_tris[_tricount].uv_indices[0],&_tris[_tricount].normal_indices[0],
					&_tris[_tricount].vertex_indices[1],&_tris[_tricount].uv_indices[1],&_tris[_tricount].normal_indices[1],
					&_tris[_tricount].vertex_indices[2],&_tris[_tricount].uv_indices[2],&_tris[_tricount].normal_indices[2]);
			_tricount++;
			break;

		default:
			break;
		}
	}

	for (int i=0;i<_vtcount;i++)
	{
		printf("UV:%f %f\n",_vts[i].u,_vts[i].v);
	}

	printf("Vertex:%d\n",_vcount);
	printf("Normales:%d\n",_vncount);
	printf("UV:%d\n\n",_vtcount);
	printf("Triangles:%d\n",_tricount);

	fclose(f);
	return true;
}


