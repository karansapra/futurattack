/*
 * OBJ3DObject.cpp
 *
 *  Created on: 7 oct. 2009
 *      Author: clement
 */

#include "OBJ3DObject.h"

OBJ3DObject::OBJ3DObject() : I3DObject() {

}

OBJ3DObject::~OBJ3DObject() {
	// TODO Auto-generated destructor stub
}

const char *OBJ3DObject::ToString()
{
	return "OBJ3DObject";
}



void OBJ3DObject::Render()
{
}



bool OBJ3DObject::Load(char *filename)
{
	float a,b,c;
	int v_count=0;
	char buffer_line[80];
	int pos=0;

	FILE * f = fopen(filename,"r");
	if (f==NULL)
		return false;


	while (!feof(f))
	{
		while ((buffer_line[pos]=fgetc(f))!='\n' && !feof(f) && pos<80-1)
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
				sscanf(buffer_line+2,"%f %f %f",&a,&b,&c);
				v_count++;
				printf("V%06d:(%f %f %f)\n",v_count,a,b,c);
			}
			break;

		default:
			break;
		}
	}


	fclose(f);
	return true;
}


