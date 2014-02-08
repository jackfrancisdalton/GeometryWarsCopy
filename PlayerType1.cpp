#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "PlayerType1.h"

#define CAMERA_MOVEMENT_SPEED 10.0
#define PLAYER_MOVEMENT_SPEED 10.0
#define PLAYER_ROTATION_SPEED 100.0
#define ROTATION_SPIKE_BALL_SPEED 220.0
#define JUMP_HEIGHT 2.5
#define SHIELD_OSCILATION_SPEED 1.5
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)
#define SHIELD_GROWTH_RATE 1.0

PlayerType1::PlayerType1(InputState *inputState)	
{
	playerX = 0.0;
	playerY = 0.0;
	rotateZ = 0.0;
	boostOn = false;
	jumpStage = 1.0;
	falling = false;
	jump = false;
	maxSpeed = 5;
	acceleration = 0.0;
	shieldTime = 0.0;
	powerORBRotate = 0.0;
	attackZ = 0.0;
}

void PlayerType1::initialise()
{
	playerTextureID = SOIL_load_OGL_texture("super_player.png",		
		SOIL_LOAD_AUTO,											
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);	

	spikeBallTextureID = SOIL_load_OGL_texture("spike_ball.png",		
		SOIL_LOAD_AUTO,							 
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	
	shieldTextureID = SOIL_load_OGL_texture("shield.png",		
		SOIL_LOAD_AUTO,							 
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	shieldHitTextureID = SOIL_load_OGL_texture("shield_hit.png",		
		SOIL_LOAD_AUTO,							 
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}


void PlayerType1::shutdown()
{
	glDeleteTextures(1, &playerTextureID);
}

void PlayerType1::onSwitchIn()
{
	glClearColor(0.0,0.0,0.0,0.0);						
}
/*
void PlayerType1::onReshape(int width, int height)
{
	
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	double aspect = app->getAspectRatio();
	gluOrtho2D(-aspect, aspect, -1.0, 1.0);				// Set a projection that takes the area -aspect to aspect in X and -1 to 1 in Y and project it to -1 to 1 in both X and Y

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	
}
*/
void PlayerType1::update(double deltaT, double prevDeltaT, InputState *inputState) 
{
	//**************************************MOVEMENT
	double playerDirSin = sin(DEG_2_RAD(-rotateZ)), playerDirCos = cos(DEG_2_RAD(-rotateZ));
	if(inputState->isKeyPressed('W'))
	{
		if (acceleration < maxSpeed) {
			acceleration += 0.001;
		}
	}
	else if(inputState->isKeyPressed('S'))
	{
		if (acceleration > -maxSpeed) {
			acceleration -= 0.001;
		}
	}
	else
	{
		if (acceleration > 0)
		{
			acceleration -= 0.003;
			if (acceleration < 0)
			{
				acceleration = 0;
			}
		}
		else if ( acceleration <= 0)
		{
			acceleration += 0.003;
			if (acceleration > 0)
			{
				acceleration = 0;
			}
		}
	}
	playerX += playerDirSin * PLAYER_MOVEMENT_SPEED * deltaT * acceleration;
	playerY += playerDirCos * PLAYER_MOVEMENT_SPEED * deltaT * acceleration;

	if(inputState->isKeyPressed('D'))
	{
		rotateZ -= PLAYER_ROTATION_SPEED * deltaT;
	}
	if(inputState->isKeyPressed('A'))
	{
		rotateZ += PLAYER_ROTATION_SPEED * deltaT;
	}
	if(inputState->isKeyPressed('Q'))
	{
		playerX += -playerDirCos * PLAYER_MOVEMENT_SPEED * deltaT;
		playerY += playerDirSin * PLAYER_MOVEMENT_SPEED * deltaT;
	}
	if(inputState->isKeyPressed('E'))
	{
		playerX += playerDirCos * PLAYER_MOVEMENT_SPEED * deltaT;
		playerY += -playerDirSin * PLAYER_MOVEMENT_SPEED * deltaT;
	}


	//**************************************ATTACK AND BOOST
	if(inputState->isKeyPressed('F'))
	{
		attackZ += PLAYER_ROTATION_SPEED * deltaT;
	}
	if(inputState->isKeyPressed(' ')) 
	{
		jump = true;
	}
	if(inputState->isKeyPressed('L')) 
	{
		boostOn = !boostOn;
	}

	//***************************************JUMPING
	if ( jump == true) //is jumping
	{
		if ( jumpStage < JUMP_HEIGHT) //is before apex
		{
			if (falling == false) //is going up
			{
				jumpStage = jumpStage + 0.002;
				if ( jumpStage  > JUMP_HEIGHT - 0.5)
				{
					falling = true; 
				}
			}
			
			else if (falling == true) //is coming back down
			{
				jumpStage = jumpStage - 0.0005;
				if ( jumpStage < 1.001 ) 
				{
					jumpStage = 1;
					jump = false;
					falling = false;
				}
			}
		} 
	}

	//*****************************************************POWER UPS
	if(powerORBOn == true) {
		powerORBRotate += (ROTATION_SPIKE_BALL_SPEED * deltaT);
		if (powerORBSize < 1.0) {
			powerORBSize += 0.001;
		}
	}
	else if(powerORBOn == false) {
		if (powerORBSize > 0.0) {
			powerORBSize -= 0.001;
		}
		if (powerORBSize == 0.0) {
			powerORBRotate = 0.0;
		}
	}

	if(boostOn == true) {
		maxSpeed = 6;
	}
	if (boostOn == false) {
		maxSpeed = 4;
	}
	
	shieldTime += (SHIELD_OSCILATION_SPEED * deltaT );

	if (shieldOn) {
		if (shieldScale < 1.0) {
			shieldScale += SHIELD_GROWTH_RATE * deltaT;
			if (shieldScale > 1.0) {
				shieldScale = 1.0;
			}
		}
	}
	else {
		if (shieldScale > 0.0) {
			shieldScale -= SHIELD_GROWTH_RATE * deltaT;
			if (shieldScale < 0.0) {
				shieldScale = 0.0;
			}
		}
	}
}

void PlayerType1::render()
{
	glTranslated(playerX, playerY, 1.0);
	glRotated(rotateZ,0.0, 0.0, 1);
	glScaled(jumpStage , jumpStage , 3.0);
	
	glBindTexture(GL_TEXTURE_2D, playerTextureID);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0, 0);
		glVertex2f(-2, -2);//bottom left

		glTexCoord2f(1, 0);
		glVertex2f(2, -2);//bottom right

		glTexCoord2f(0, 1);
		glVertex2f(-2, 3.5);//top left

		glTexCoord2f(1, 0);
		glVertex2f(2, -2);//bottom right

		glTexCoord2f(1, 1);
		glVertex2f(2, 3.5);//top right

		glTexCoord2f(0, 1);
		glVertex2f(-2, 3.5);//top left
	glEnd();

	glDisable (GL_BLEND);
	glDisable(GL_TEXTURE_2D);
		//***********************************************************POWERUP SPIKEBALL 
		glPushMatrix();
			glScaled(powerORBSize, powerORBSize, 1.0);
			glRotated(powerORBRotate,0.0, 0.0, 1);
			glTranslated(0.0, powerORBTranslateY, 0.0);
			glRotated(powerORBRotate,0.0, 0.0, 1);
	
			glBindTexture(GL_TEXTURE_2D, spikeBallTextureID);
			glEnable(GL_TEXTURE_2D);
			glEnable (GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
			glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 1.0f, 1.0f);

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

			glDisable (GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		//*************************************************SHEILD
		glPushMatrix();
			float scale = (2 + sin(shieldTime * 4) / 3.0f) * shieldScale; 
			
			glScaled(scale, scale, 1.0);
	
			glBindTexture(GL_TEXTURE_2D, shieldTextureID);
			glEnable(GL_TEXTURE_2D);
			glEnable (GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
			glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 1.0f, 1.0f);

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

			glDisable (GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	glPopMatrix();
}

void PlayerType1::onKeyUp(int key)										
{
	
	if(key == '1') {
		if (!shieldOn) {
			shieldScale = 0.0;
			shieldTime = 0.0;
			shieldOn = true;
		}
		else {
			shieldOn = false;
		}
	}
	if (key == '2') {
		powerORBOn = !powerORBOn;
	}
	if(key =='3') 
	{
		
		shieldTextureID = shieldHitTextureID;
	}
}
