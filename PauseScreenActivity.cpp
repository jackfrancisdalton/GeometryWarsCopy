#include <windows.h>		// Header File For Windows
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

#include "SOIL.h"

#include "OpenGLApplication.h"			// Needed for OpenGLApplication method calls
#include "GameActivity.h"
#include "PauseScreenActivity.h"



PauseScreenActivity::PauseScreenActivity(OpenGLApplication *app)
	: Activity(app)		// Call the super constructor
{
}


void PauseScreenActivity::initialise()
{
	// Initialise the activity; called at application start up

	// Load the start screen image as a texture using the SOIL library
	textureID = SOIL_load_OGL_texture("select_screen.png",		// filename
		SOIL_LOAD_AUTO,											// 
		SOIL_CREATE_NEW_ID,										// ask SOIL to create a new OpenGL texture ID for us
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);				// generate Mipmaps and invert Y
}


void PauseScreenActivity::shutdown()
{
	// Shutdown the activity; called at application finish

	// Delete the texture
	glDeleteTextures(1, &textureID);
}


/*
*
* ACTIVITY METHODS
* Put your application/game code here
*
*/
void PauseScreenActivity::onSwitchIn()
{
	// Activity switched in

	glClearColor(0.0,0.0,0.0,0.0);						//sets the clear colour to black
}

void PauseScreenActivity::onReshape(int width, int height)
{
	// Screen resized
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	double aspect = app->getAspectRatio();
	gluOrtho2D(-aspect, aspect, -1.0, 1.0);				// Set a projection that takes the area -aspect to aspect in X and -1 to 1 in Y and project it to -1 to 1 in both X and Y

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void PauseScreenActivity::render()
{
	// OpenGL render calls go in this method

	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Identity matrix
	glLoadIdentity();

	// Bind our start screen texture to GL_TEXTURE_2D
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Enable 2D texturing
	glEnable(GL_TEXTURE_2D);

	// Use two triangles to make a square, with texture co-ordinates for each vertex
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

	// Disable 2D texturing
	glDisable(GL_TEXTURE_2D);

	glFlush();
}



void PauseScreenActivity::onKeyUp(int key)										// Called when key released
{
	if (key == VK_RETURN)
	{
		app->setCurrentActivity(app->game);
	}
}
