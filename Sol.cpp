#include "Sol.h"


void Sol::DibujarSol(float x, float y, float z, GLMmodel* m) {

	glPushMatrix();
	glTranslatef(x, y, z);
	glmDraw(m, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}