#include <windows.h>		// Header File For Windows
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

#include "SOIL.h"

#include "OpenGLApplication.h"			
#include "GameActivity.h"
#include "PauseScreenActivity.h"



PauseScreenActivity::PauseScreenActivity(OpenGLApplication *app)
	: Activity(app)		
{
}


void PauseScreenActivity::initialise()
{
	textureID = SOIL_load_OGL_texture("pause_screen.png",		
		SOIL_LOAD_AUTO,											 
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);				
}


void PauseScreenActivity::shutdown()
{
	glDeleteTextures(1, &textureID);
}

void PauseScreenActivity::onSwitchIn()
{
	glClearColor(0.0,0.0,0.0,0.0);						
}

void PauseScreenActivity::onReshape(int width, int height)
{
	glViewport(0,0,width,height);						

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();									

	double aspect = app->getAspectRatio();
	gluOrtho2D(-aspect, aspect, -1.0, 1.0);				

	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();									
}

void PauseScreenActivity::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLES);
		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);

		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);


		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(1, 1);
		glVertex2f(1, 1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glFlush();
}



void PauseScreenActivity::onKeyDown(int key)										
{
	if (key == VK_RETURN)
	{
		app->setCurrentActivity(app->game);
	}
	else if (key == VK_DOWN)
	{
		app->setCurrentActivity(app->selectScreen);
	}
}
