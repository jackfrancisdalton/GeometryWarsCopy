#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "ScoreOrb.h"
#include <random>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)

ScoreOrb::ScoreOrb() : Collectable()
{
	objectPoly = polygon(4);
	objectPolyN = polygon(4);
	size = 4;
	rot = 1;
}

void ScoreOrb::initialise()
{
	collectableTextureId = SOIL_load_OGL_texture("blue-orb.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	posX = (rand() % 10 - 5) * 10;
	posY = (rand() % 10 - 5) * 10;

	int minus = -size / 2;
	int positive = size / 2;

	objectPolyN.vert[0].x = objectPoly.vert[0].x = minus;
	objectPolyN.vert[0].y = objectPoly.vert[0].y = minus;
	objectPolyN.vert[1].x = objectPoly.vert[1].x = positive;
	objectPolyN.vert[1].y = objectPoly.vert[1].y = minus;
	objectPolyN.vert[2].x = objectPoly.vert[2].x = positive;
	objectPolyN.vert[2].y = objectPoly.vert[2].y = positive;
	objectPolyN.vert[3].x = objectPoly.vert[3].x = minus;
	objectPolyN.vert[3].y = objectPoly.vert[3].y = positive;
}

void ScoreOrb::update(double deltaT, double prevDeltaT)
{
	if (rot < 360) {
		rot += 30 * deltaT;
	}
	else {
		rot = 0;
	}

	setTraMat(mb1, posX, posY, 0.0);
	setRotMat(mb2, M_PI*rot / 180.0, 2);
	MultMat(mb1, mb2, mb);
	for (int i = 0; i<4; ++i)MultMatPre2DPoint(mb, &objectPoly.vert[i], &objectPolyN.vert[i]);
}

void ScoreOrb::render()
{
	glPushMatrix();

	glTranslated(posX, posY, 1.0);
	glRotated(rot, 0.0, 0.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, collectableTextureId);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0, 0.0); glVertex2f(-size, -size);
	glTexCoord2f(0.0, 1.0); glVertex2f(size, -size);
	glTexCoord2f(1.0, 1.0); glVertex2f(size, size);
	glTexCoord2f(1.0, 0.0); glVertex2f(-size, size);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
