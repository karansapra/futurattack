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
}

StandardMaterial::~StandardMaterial() {

}

void StandardMaterial::Apply()
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glDisable(GL_TEXTURE_2D);
	glColor3fv((GLfloat*)&ambient);
}


