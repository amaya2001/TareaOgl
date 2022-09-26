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

class Sol
{
public:
	Sol() {};
	void DibujarSol(float x, float y, float z, GLMmodel* m);
};
