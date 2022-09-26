#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
//#include <FreeImage.h> *** Para Textura: Incluir librería
#include "FreeImage/FreeImage.h"

class Castillo
{
public:
	Castillo() {};
	void DibujarCastillo(float x, float y, float z, GLMmodel* m, GLuint t);
};
