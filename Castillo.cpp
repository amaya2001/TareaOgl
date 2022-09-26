#include "Castillo.h";

void Castillo::DibujarCastillo(float x, float y, float z, GLMmodel* m, GLuint t) {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, t);
	glmDraw(m, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
}