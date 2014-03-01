#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "EnemyType1.h"
#include <random>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)

EnemyType1::EnemyType1() : Enemy()
{
	posX = (rand() % 50 - 20) * 10;
	posY = (rand() % 50 - 20) * 10;
	rot = 0.0;
	textureX = textureY = 0.25;
	refreshWait = 1000;
	refreshIndex = 1;
	frameCounter = 0.0;
	speed = (rand() % 10) + 1;
	HitRadius = 1;
}

void EnemyType1::initialise()
{
	enemyTextureId = SOIL_load_OGL_texture("enemy-sprite-sheet.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void EnemyType1::update(double deltaT, double prevDeltaT, double playerX, double playerY)
{

	frameCounter += 1;
	if (frameCounter > 100) {
		if (textureX < 1) {
			textureX += .25;
			frameCounter = 0.0;
		}
		else {
			textureX = 0.25;
			frameCounter = 0.0;
		}
	}

	double rotRads = atan2(posY - playerY, posX - playerX); //trig function for angle of zombie
	rot = rotRads * (180.0 / M_PI); // convert to deg

	double playerDirSin = sin(rotRads); //calculates direction for y
	double playerDirCos = cos(rotRads); //calculates direction for x

	posX -= playerDirCos * speed * deltaT;
	posY -= playerDirSin * speed * deltaT;
}

void EnemyType1::render()
{
	glPushMatrix();

	glTranslated(posX, posY, 0.0);
	glRotated(rot, 0.0, 0.0, 1);

	glBindTexture(GL_TEXTURE_2D, enemyTextureId);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(textureX - 0.25, 0);
	glVertex2f(-1, -1);//bottom left

	glTexCoord2f(textureX, 0);
	glVertex2f(1, -1);//bottom right

	glTexCoord2f(textureX - 0.25, 1.0);
	glVertex2f(-1, 1);//top left

	glTexCoord2f(textureX, 0);
	glVertex2f(1, -1);//bottom right

	glTexCoord2f(textureX, 1.0);
	glVertex2f(1, 1);//top right

	glTexCoord2f(textureX - 0.25, 1.0);
	glVertex2f(-1, 1);//top left
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
