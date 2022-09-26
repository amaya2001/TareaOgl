#include "Palmera.h"


void Palmera::DibujarPalmera(float x, float y, float z, GLMmodel* m) {

	glPushMatrix();
	glTranslatef(x, y, z);
	glmDraw(m, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}