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
	for (int i=0;i<OBJ_FILE_MAX_MATERIALS;i++)
		_parsed_materials[i]=NULL;
}

OBJ3DObject::~OBJ3DObject() {
	for (int i=0;i<_nmeshes;i++)
		if (_meshes[i]!=NULL)
			delete _meshes[i];

	for (int i=0;i<_nparsed_materials;i++)
		if (_parsed_materials[i]!=NULL)
			delete _parsed_materials[i];
}

void OBJ3DObject::SwitchTextureOrigin()
{
	_switch = true;
}

void OBJ3DObject::_parse_mtl_file(char *file)
{
	FILE * f = fopen(file,"r");
	if (f==NULL)
		return;

	char buffer_line[OBJ_FILE_LINE_LENGTH];
	int pos = 0;

	_nparsed_materials = 0;

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
		case 'n':
			if (buffer_line[1]=='e' && buffer_line[2]=='w')
			{
				//newmtl
				char mtl_name[128];
				sscanf(buffer_line,"newmtl %s",mtl_name);
				printf("New Material : %s\n",mtl_name);
				_parsed_materials[_nparsed_materials] = new StandardMaterial(mtl_name);
				_nparsed_materials++;
			}
			break;

		case 'K':
			if (buffer_line[1]=='d' && _nparsed_materials>0)
			{
				//Ambient color
				if (_parsed_materials[_nparsed_materials-1]!=NULL)
				{
					RGB ambient;
					sscanf(buffer_line,"Kd %f %f %f",&ambient.R,&ambient.G,&ambient.B);
					((StandardMaterial*)_parsed_materials[_nparsed_materials-1])->ambient = ambient;
				}
			}
			break;

		default:
			break;
		}
	}

	fclose(f);

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
	//RAZ du nb de meshes
	_nmeshes = 0;

	//Comptage total des vertices dans le fichier de base
	int vertex_count=0;
	int normal_count=0;
	int texture_count=0;

	//Comptage des vertices par mesh
	int vertex_list_count=0;
	int normal_list_count=0;
	int texture_list_count=0;

	//Pour stocker la ligne courante du .OBJ
	char buffer_line[OBJ_FILE_LINE_LENGTH];
	//Index pour le positionnement
	int pos=0;

	//Pour les index des vertices,normales,texcoords
	int v1, v2, v3;
	int n1, n2, n3;
	int t1, t2, t3;

	//Indice général
	int i;

	//On essaye d'ouvrir le fichier, sinon on retourne l'echec
	FILE * f = fopen(filename,"r");
	if (f==NULL)
		return false;

	//Allocation des vertex en dyn, pour ne pas prendre de la place longtemps
	Vertex3f * vertex = new Vertex3f[OBJ_FILE_MAX_VERTEX];
	Vertex3f * vertex_list = new Vertex3f[OBJ_FILE_MAX_VERTEX*3];
	Vertex3f * normal = new Vertex3f[OBJ_FILE_MAX_NORMALS];
	Vertex3f * normal_list = new Vertex3f[OBJ_FILE_MAX_NORMALS*3];
	Vertex2f * texture = new Vertex2f[OBJ_FILE_MAX_TEXTCOORDS];
	Vertex2f * texture_list = new Vertex2f[OBJ_FILE_MAX_TEXTCOORDS*3];

	//On parcours toutes les lignes
	while (!feof(f))
	{
		//Capture d'une ligne
		while ((buffer_line[pos]=fgetc(f))!='\n' && !feof(f) && pos<OBJ_FILE_LINE_LENGTH-1)
			pos++;
		//Zero terminal pour clore la chaine correctement
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
				//On est dans le cas d'un vertex simple, de positionnement, on ajoute a la liste, on
				//pourra y accéder via un index
				sscanf(buffer_line+2,"%f %f %f",
						&vertex[vertex_count].x,
						&vertex[vertex_count].y,
						&vertex[vertex_count].z);
				vertex_count++;
			} else if (buffer_line[1]=='n')
			{
				//On est dans le cas d'une normale on l'ajoute a la liste, on
				//pourra y accéder via un index
				sscanf(buffer_line+3,"%f %f %f",
						&normal[normal_count].x,
						&normal[normal_count].y,
						&normal[normal_count].z);
				normal_count++;

			} else if (buffer_line[1]=='t')
			{
				//On est dans le cas d'une coord UV, on l'ajoute a la liste, on
				//pourra y accéder via un index
				sscanf(buffer_line+3,"%f %f",
						&texture[texture_count].u,
						&texture[texture_count].v);
				if (_switch)
					texture[texture_count].v = 1.0-texture[texture_count].v;
				texture_count++;
			}
			break;

		case 'o':
			//Un nouvel objet est detecte, on cree un mesh au fur et a mesure

			//On recupere son nom
			char name[32];
			sscanf(buffer_line+2,"%s",name);

			//On enregistre le mesh d'avant correctement
			if (_nmeshes>0)
			{
				_meshes[_nmeshes-1]->SetVertexList(vertex_list,vertex_list_count);
				_meshes[_nmeshes-1]->SetNormalList(normal_list,normal_list_count);
				_meshes[_nmeshes-1]->SetTexCoordList(texture_list,texture_list_count);
				_meshes[_nmeshes-1]->BuildUp();

				//Reinit des tableaux
				vertex_list_count=0;
				normal_list_count=0;
				texture_list_count=0;
			}

			//Nouveau mesh
			_meshes[_nmeshes] = new Mesh(name);
			_nmeshes++;

			break;

		case 'u':
			if (buffer_line[1]=='s' && buffer_line[2]=='e')
			{
				//usemtl : on veut que l'objet qui suit ait un materiau
				char mtl_name[128];
				sscanf(buffer_line,"usemtl %s",mtl_name);
				printf("parsed: %d\n",_nparsed_materials);
				//On cherche le nom du material dans la liste
				for (i=0;i<_nparsed_materials;i++)
				{
					printf("%s\n",_parsed_materials[i]->GetMaterialName());
					if (strcmp(mtl_name,_parsed_materials[i]->GetMaterialName())==0)
					{

						_meshes[_nmeshes-1]->SetMaterial(_parsed_materials[i]);
						break;
					}
				}
			}
			break;

		case 'm':
			if (buffer_line[1]=='t' && buffer_line[2]=='l')
			{
				//On est dans le cas ou un fichier de material est specifie
				//On reconstruit le path total
				char dir[256];
				char mtlfile[128];
				sscanf(&buffer_line[7],"%s",mtlfile);
				strcpy(dir,filename);
				int pos = strlen(dir)-1;
				while (dir[pos]!='\\' && dir[pos]!='/')
					pos--;

				dir[pos+1]=0x00;
				strcpy(&dir[pos+1],mtlfile);

				//On parse le MTL, de maniere a avoir les materiaux charges correctement
				_parse_mtl_file(dir);
			}
			break;

		case 'f':
			//Une nouvelle face

			//On teste la presence de double / ou pas, ce qui donne l'info s'il y a UV coords ou pas
			i=0;
			while (buffer_line[i]!='/')
				i++;


			if (buffer_line[i+1]!='/')
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

			//Il y a pas de double /, on a des coords UV, on traite en csq
			if (buffer_line[i+1]!='/')
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

	//Cloture du fichier
	fclose(f);

	//On enregistre le dernier mesh en cours
	_meshes[_nmeshes-1]->SetVertexList(vertex_list,vertex_list_count);
	_meshes[_nmeshes-1]->SetNormalList(normal_list,normal_list_count);
	_meshes[_nmeshes-1]->SetTexCoordList(texture_list,texture_list_count);
	_meshes[_nmeshes-1]->BuildUp();

	//On libere la memoire des tableaux, tout est dans la carte graphique maintenant!
	delete[] vertex;
	delete[] vertex_list;
	delete[] normal;
	delete[] normal_list;
	delete[] texture;
	delete[] texture_list;

	return true;
}


