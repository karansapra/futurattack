/*
 * StandardMaterial.cpp
 *
 *  Created on: 13 oct. 2009
 *      Author: clement
 */

#include "StandardMaterial.h"

StandardMaterial::StandardMaterial(const char * material_name) {
	strcpy(_material_name,material_name);
	ambient.R = 1.0;
	ambient.G = 1.0;
	ambient.B = 1.0;
	ambient.A = 1.0;

	specular.R = 1.0;
	specular.G = 1.0;
	specular.B = 1.0;
	specular.A = 1.0;

	shine = 128;
}

StandardMaterial::~StandardMaterial() {

}

void StandardMaterial::Apply()
{
	if (ambient.A!=1.0)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat*)&specular);
	glMateriali(GL_FRONT,GL_SHININESS,shine);
	glColor4fv((GLfloat*)&ambient);
}


