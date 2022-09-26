//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

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
#include "Barco.h"
#include "Palmera.h"
#include "Castillo.h"
#include "Sol.h"

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   cwc::glShader* shader1; //Para Textura: variable para abrir los shader de textura
   cwc::glShader* shader2;
   cwc::glShader* shader3;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   GLMmodel* objmodel_ptr;
   GLMmodel* objmodel_ptr1; //*** Para Textura: variable para objeto texturizado
   GLMmodel* objmodel_ptr2;
   GLMmodel* objmodel_ptr3;
   GLuint texid; //*** Para Textura: variable que almacena el identificador de textura
   bool xIzq, xDer;
   float xPos;
   Barco* _Barco;
   Palmera* _Palmera;
   Castillo* _Castillo;
   Sol* _Sol;

public:
	myWindow(){}

	//*** Para Textura: aqui adiciono un método que abre la textura en JPG
	void initialize_textures(void)
	{
		int w, h;
		GLubyte* data = 0;
		//data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
		//std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;

		//dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Loading JPG file
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType("./Mallas/piedra.jpg", 0),
			"./Mallas/piedra.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

		FreeImage_Unload(pImage);
		//
		glEnable(GL_TEXTURE_2D);
	}

	void moverX() {
		if (xDer == true) {
			xPos = xPos + 0.01;
		}
		if (xIzq == true) {
			xPos = xPos - 0.01;
		}

	}
	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!

      glPushMatrix();
	  //glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);
	  moverX();
	  glTranslatef(xPos, 0, -1);
	  glPushMatrix();

		  if (shader) shader->begin();
		  
			  glPushMatrix();
				_Barco->DibujarBarco(-1.0f, -0.5f, 1.0f, objmodel_ptr);		  
			  glPopMatrix();
	
		  if (shader) shader->end();

		  if (shader2) shader2->begin();

		  glPushMatrix();
			_Palmera->DibujarPalmera(1.5f, 0.0f, 1.0f, objmodel_ptr2);
		  glPopMatrix();

		  if (shader2) shader2->end();

		  if (shader3) shader2->begin();

		  glPushMatrix();
			_Sol->DibujarSol(-1.0f, 1.5f, 0.0f, objmodel_ptr3);
		  glPopMatrix();

		  if (shader3) shader2->end();

		  //*** Para Textura: llamado al shader para objetos texturizados
		  if (shader1) shader1->begin();

			  glPushMatrix();
			  _Castillo->DibujarCastillo(0.0f, 0.0f, 0.0f, objmodel_ptr1, texid );
			  glPopMatrix();
		  //glutSolidTeapot(1.0);
		  if (shader1) shader1->end();
	  glPopMatrix();

      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		xIzq = false;
		xDer = false;
		xPos = 0;

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

		shader2 = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
		if (shader2 == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shader2->GetProgramObject();
		}

	 //*** Para Textura: abre los shaders para texturas
		shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader1 == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shader1->GetProgramObject();
		}

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

	  //Abrir mallas
	  objmodel_ptr = NULL;
	  _Barco = new Barco();
	  _Palmera = new Palmera();
	  _Castillo = new Castillo();
	  _Sol = new Sol();

	  if (!objmodel_ptr)
	  {
		  objmodel_ptr = glmReadOBJ("./Mallas/bote1.obj");
		  if (!objmodel_ptr)
			  exit(0);

		  glmUnitize(objmodel_ptr);
		  glmFacetNormals(objmodel_ptr);
		  glmVertexNormals(objmodel_ptr, 90.0);
	  }

	  objmodel_ptr2 = NULL;

	  if (!objmodel_ptr2)
	  {
		  objmodel_ptr2 = glmReadOBJ("./Mallas/palmera3_.obj");
		  if (!objmodel_ptr2)
			  exit(0);

		  glmUnitize(objmodel_ptr2);
		  glmFacetNormals(objmodel_ptr2);
		  glmVertexNormals(objmodel_ptr2, 90.0);
	  }

	  objmodel_ptr3 = NULL;

	  if (!objmodel_ptr3)
	  {
		  objmodel_ptr3 = glmReadOBJ("./Mallas/sol_12.obj");
		  if (!objmodel_ptr3)
			  exit(0);

		  glmUnitize(objmodel_ptr3);
		  glmFacetNormals(objmodel_ptr3);
		  glmVertexNormals(objmodel_ptr3, 90.0);
	  }

	  //*** Para Textura: abrir malla de objeto a texturizar
	  objmodel_ptr1 = NULL;

	  if (!objmodel_ptr1)
	  {
		  objmodel_ptr1 = glmReadOBJ("./Mallas/Castillo.obj");
		  if (!objmodel_ptr1)
			  exit(0);

		  glmUnitize(objmodel_ptr1);
		  glmFacetNormals(objmodel_ptr1);
		  glmVertexNormals(objmodel_ptr1, 90.0);
	  }
 
	  //*** Para Textura: abrir archivo de textura
	  initialize_textures();
      DemoLight();

	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{   
		switch (cAscii){
			case 27:
				this->Close();
				break;
			case 'a':
				xIzq = true;
				break;
			case 'd':
				xDer = true;
				break;
		}
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
		switch (cAscii) {
		case 'a':
			xIzq = false;
			break;
		case 'd':
			xDer = false;
			break;
		}
      if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     
     // ------------------------------------------- 
     // Lighting parameters:
     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.0f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};


     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

