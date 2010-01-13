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
		case 'n':
			/*
			Normal
			*/			
			sscanf((const char *)line,"v %f %f %f",&v.x,&v.y,&v.z);
			mesh.normals.push_back(v);
			break;
		case 't':
			v.z = 0;
			sscanf((const char *)line,"vt %f %f",&v.x,&v.y);
			mesh.texcoords.push_back(v);
			break;

		default:
			break;
		}
		break;
	case 'f':
		/*
		Tri face
		*/
		if (mesh.texcoords.size()==0)
			sscanf((const char *)line,"f %u//%u %u//%u %u//%u",indices,indices+1,indices+2,indices+3,indices+4,indices+5);
		else
			sscanf((const char *)line,"f %u/%u/%u %u/%u/%u %u/%u/%u",indices,indices+6,indices+1,indices+2,indices+7,indices+3,indices+4,indices+8,indices+5);
		f.indexes[0] = *indices - 1;
		f.indexes[1] = *(indices+2) - 1;
		f.indexes[2] = *(indices+4) - 1;
		f.nindexes[0] = *(indices+1) - 1;
		f.nindexes[1] = *(indices+3) - 1;
		f.nindexes[2] = *(indices+5) - 1;
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
	static VertexArray::iterator i;
	

	U8 buffer[128];

	FILE * f = fopen((const char *)model_file,"r");
	if (f==NULL)
		return false;

	while (freadline(f,buffer,128)==0)
	{
		LoadObjFileStateMachine(buffer,mesh);
	}

	/*
	Bounding sphere building
	*/
	Vector3 mean;
	for (i=mesh.vertices.begin();i!=mesh.vertices.end();i++)
		mean += *i;

	mean /= (REAL)mesh.vertices.size();
	mesh.boundingsphere.center = mean;

	REAL max_dist=0;
	REAL d;
	Vector3 dist_to_point;
	for (i=mesh.vertices.begin();i!=mesh.vertices.end();i++)
	{
		dist_to_point = (*i)-mean;
		d = dist_to_point.Length2();
		if (d>=max_dist)
			max_dist = d;
	}

	mesh.boundingsphere.radius = sqrt_real(max_dist);

	/*
	AABB Computing
	*/
	Vector3 maxs, mins;
	maxs = mesh.vertices[0];
	mins = mesh.vertices[0];
	for (i=mesh.vertices.begin();i!=mesh.vertices.end();i++)
	{
		if (i->x > maxs.x)
			maxs.x = i->x;
		if (i->y > maxs.y)
			maxs.y = i->y;
		if (i->z > maxs.z)
			maxs.z = i->z;

		if (i->x < mins.x)
			mins.x = i->x;
		if (i->y < mins.y)
			mins.y = i->y;
		if (i->z < mins.z)
			mins.z = i->z;
	}
	
	mesh.aabb.center = (maxs+mins)/2;
	mesh.aabb.widths = maxs-mins;

	return true;
}