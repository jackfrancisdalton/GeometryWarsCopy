#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>			
#include "SOIL.h"
#include "OpenGLApplication.h"			
#include "EndScreenActivity.h"

EndScreenActivity::EndScreenActivity(OpenGLApplication *app)
	: Activity(app)
{
}

void EndScreenActivity::initialise()
{
	textureID = SOIL_load_OGL_texture("end_screen.png",	
		SOIL_LOAD_AUTO,											
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);			
}

void EndScreenActivity::shutdown()
{
	glDeleteTextures(1, &textureID);
}

void EndScreenActivity::onSwitchIn()
{
	glClearColor(0.0,0.0,0.0,0.0);						
}

void EndScreenActivity::onReshape(int width, int height)
{
	glViewport(0,0,width,height);						

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();								

	double aspect = app->getAspectRatio();
	gluOrtho2D(-aspect, aspect, -1.0, 1.0);				

	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();									
}

void EndScreenActivity::render()
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

void EndScreenActivity::onKeyUp(int key)										
{
	if (key == ' ')
	{
		app->finish();
	}
}
