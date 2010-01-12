#include "objfileloader.h"

unsigned char freadline(FILE * f, unsigned char * buffer, unsigned int max_size)
{
	unsigned int index=0;
	while (index<max_size && buffer[index-1]!='\n' && !feof(f))
	{
		buffer[index] = fgetc(f);
		index++;
	}
	
	if (feof(f))
		return 1;

	if (buffer[index-1]=='\n')
		buffer[index-1]=0;
	return 0;
}

void LoadObjFileStateMachine(U8 * line, VertexArray & varray)
{
	static Vector3 v;

	switch (line[0])
	{
	case 'v':
		switch (line[1])
		{
		case ' ':
			/*
			Simple vertex
			*/			
			sscanf((const char *)line,"v %f %f %f",&v.x,&v.y,&v.z);
			varray.push_back(v);
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

void LoadObjFileStateMachine(U8 * line, Mesh & mesh)
{
	static Vector3 v;
	static Mesh::Face f;
	static U32 indices[9];

	switch (line[0])
	{
	case 'v':
		switch (line[1])
		{
		case ' ':
			/*
			Simple vertex
			*/			
			sscanf((const char *)line,"v %f %f %f",&v.x,&v.y,&v.z);
			mesh.vertices.push_back(v);
			break;

		default:
			break;
		}
		break;
	case 'f':
		/*
		Tri face
		*/
		sscanf((const char *)line,"f %u//%u %u//%u %u//%u",indices,indices+1,indices+2,indices+3,indices+4,indices+5);
		f.indexes[0] = *indices - 1;
		f.indexes[1] = *(indices+2) - 1;
		f.indexes[2] = *(indices+4) - 1;
		mesh.faces.push_back(f);
		break;
	default:
		break;
	}
}

bool LoadObjFile(U8 * model_file, VertexArray & varray)
{
	U8 buffer[128];

	FILE * f = fopen((const char *)model_file,"r");
	if (f==NULL)
		return false;

	while (freadline(f,buffer,128)==0)
	{
		LoadObjFileStateMachine(buffer,varray);
	}

	return true;
}

bool LoadObjFile(U8 * model_file, Mesh & mesh)
{
	U8 buffer[128];

	FILE * f = fopen((const char *)model_file,"r");
	if (f==NULL)
		return false;

	while (freadline(f,buffer,128)==0)
	{
		LoadObjFileStateMachine(buffer,mesh);
	}

	return true;
}