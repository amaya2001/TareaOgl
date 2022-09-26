#include "Barco.h";

void Barco::DibujarBarco(float x, float y, float z, GLMmodel * m) {

	glPushMatrix();
	glTranslatef(x, y, z);
	glmDraw(m, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}