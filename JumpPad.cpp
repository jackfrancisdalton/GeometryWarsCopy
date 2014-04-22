#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "JumpPad.h"
#include <random>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)

JumpPad::JumpPad() : Object()
{
	objectPoly = polygon(4);
	objectPolyN = polygon(4);
	size = 4;
	rot = 1;
}

void JumpPad::initialise()
{
	objectTextureId = SOIL_load_OGL_texture("jump-pad.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	posX = (rand() % 10 - 5) * 10;
	posY = (rand() % 10 - 5) * 10;

	objectPolyN.vert[0].x = objectPoly.vert[0].x = -size;
	objectPolyN.vert[0].y = objectPoly.vert[0].y = -size;
	objectPolyN.vert[1].x = objectPoly.vert[1].x = size;
	objectPolyN.vert[1].y = objectPoly.vert[1].y = -size;
	objectPolyN.vert[2].x = objectPoly.vert[2].x = size;
	objectPolyN.vert[2].y = objectPoly.vert[2].y = size;
	objectPolyN.vert[3].x = objectPoly.vert[3].x = -size;
	objectPolyN.vert[3].y = objectPoly.vert[3].y = size;
}

void JumpPad::update(double deltaT, double prevDeltaT)
{
	setTraMat(mb1, posX, posY, 0.0);
	setRotMat(mb2, M_PI*rot / 180.0, 2);
	MultMat(mb1, mb2, mb);
	for (int i = 0; i<4; ++i)MultMatPre2DPoint(mb, &objectPoly.vert[i], &objectPolyN.vert[i]);
}

void JumpPad::render()
{
	glPushMatrix();

	glTranslated(posX, posY, 1.0);
	glRotated(1.0, 0.0, 0.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, objectTextureId);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-size, -size);
	glTexCoord2f(0.0, 1.0); glVertex2f(size, -size);
	glTexCoord2f(1.0, 1.0); glVertex2f(size, size);
	glTexCoord2f(1.0, 0.0); glVertex2f(-size, size);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
