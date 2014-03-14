#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "PlayerShip.h"

#define CAMERA_MOVEMENT_SPEED 10.0
#define PLAYER_MOVEMENT_SPEED 10.0
#define ROTATION_SPIKE_BALL_SPEED 500.0
#define RESPAWN_STATE_TIME 20.0
#define JUMP_HEIGHT 2.5
#define SHIELD_OSCILATION_SPEED 1.5
#define SHIELD_GROWTH_RATE 1.0
#define FLAME_OSCILATION_SPEED 1.5
#define FLAME_GROWTH_RATE 1.0
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)



PlayerShip::PlayerShip()
{
}

PlayerShip::PlayerShip(int shipID)
{
	playerX = 0.0;
	playerY = 0.0;
	rotateZ = 0.0;
	boostOn = false;
	jumpStage = 1.0;
	falling = false;
	jump = false;
	shieldOn = false;
	shieldTime = 0.0;
	shieldScale = 0.0;
	collisionWait = 0.0;
	respawnState = false;
	respawnTimer = 0.0;
	lives = 3;
	powerORBSize = 0.0;
	powerORBMaxSize = 2.0;
	powerORBTranslateY = 2.0;
	maxSpeed = defaultMaxSpeed = 6.0;
	currentSpeed = 0.0;
	rotationSpeed = 150;
	rotateZ = 0.0;
	acceleration = 0.01;
	decceleration = 0.02;
	shipChoice = shipID;
	rocketFlamesScaleY = 0.0;
	rocketFlamesScaleX = 0.0;
	powerORBOn = false;
	boostOn = false;
	directionChangeSpeed = 0.1;
	respawnstateOpacity = 1.0;
	playerPoly = polygon(4);
	playerPolyN = polygon(4);
	boosterR = 1.0;
	boosterG = 1.0;
	boosterB = 1.0;

	if (shipChoice == 1) {
		rotationSpeed = 500;
	}
	else if(shipChoice == 2) {
		acceleration = 0.04;
	}
	else if (shipChoice == 3) {
		defaultMaxSpeed = 20.0;
	}

	boostSpeed = defaultMaxSpeed + 2.0;
}

void PlayerShip::initialise()
{
	if (shipChoice == 1) {
		playerTextureID = SOIL_load_OGL_texture("playerSkin3.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	}
	else if (shipChoice == 2) {
		playerTextureID = SOIL_load_OGL_texture("ship-sprite-sheet.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	}
	else {
		playerTextureID = SOIL_load_OGL_texture("playerSkin2.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	}
		
	spikeBallTextureID = SOIL_load_OGL_texture("spike_ball.png",		
		SOIL_LOAD_AUTO,							 
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	rocketBooster = SOIL_load_OGL_texture("rocketBooster.png",
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


	playerPolyN.vert[0].x = playerPoly.vert[0].x = -2;
	playerPolyN.vert[0].y = playerPoly.vert[0].y = -2;
	playerPolyN.vert[1].x = playerPoly.vert[1].x = 2;
	playerPolyN.vert[1].y = playerPoly.vert[1].y = -2;
	playerPolyN.vert[2].x = playerPoly.vert[2].x = 2;
	playerPolyN.vert[2].y = playerPoly.vert[2].y = 4;
	playerPolyN.vert[3].x = playerPoly.vert[3].x = -2;
	playerPolyN.vert[3].y = playerPoly.vert[3].y = 4;
}

void PlayerShip::shutdown()
{
	glDeleteTextures(1, &playerTextureID);
}

void PlayerShip::onSwitchIn()
{
	glClearColor(0.0,0.0,0.0,0.0);						
}

void PlayerShip::update(double deltaT, double prevDeltaT, InputState *inputState)
{
	double playerDirSin = sin(DEG_2_RAD(-rotateZ)), playerDirCos = cos(DEG_2_RAD(-rotateZ));

	if(inputState->isKeyPressed('W'))
	{
		if (currentSpeed > 0) 
		{
			if (currentSpeed < maxSpeed) {
				currentSpeed += acceleration;
			}
			if (rocketFlamesScaleY < 1.0)
			{
				rocketFlamesScaleY += 0.006;
			}
			if (rocketFlamesScaleX < 1.0)
			{
				rocketFlamesScaleX += 0.006;
			}
		}
		else
		{
			if (currentSpeed < maxSpeed) {
				currentSpeed += directionChangeSpeed;
			}
			if (rocketFlamesScaleY < 1.0)
			{
				rocketFlamesScaleY += 0.006;
			}
			if (rocketFlamesScaleX < 1.0)
			{
				rocketFlamesScaleX += 0.006;
			}
		}
	}

	else if(inputState->isKeyPressed('S'))
	{
		if (currentSpeed > -maxSpeed) {
			if (currentSpeed < 0) {
				currentSpeed -= acceleration;
			}
			else{
				currentSpeed -= 0.1;
			}
		}
		if (rocketFlamesScaleY > 0.0)
		{
			rocketFlamesScaleY -= 0.006;
		}
		if (rocketFlamesScaleX > 0.0)
		{
			rocketFlamesScaleX -= 0.006;
		}
	}
	else
	{
		if (currentSpeed > 0)
		{
			currentSpeed -= decceleration;
			if (currentSpeed < 0)
			{
				currentSpeed = 0;
			}
		}
		else if (currentSpeed <= 0)
		{
			currentSpeed += decceleration;
			if (currentSpeed > 0)
			{
				currentSpeed = 0;
			}
		}
		if (rocketFlamesScaleY > 0.0)
		{
			rocketFlamesScaleY -= 0.006;
		}
		if (rocketFlamesScaleX > 0.0)
		{
			rocketFlamesScaleX -= 0.006;
		}
	}

	playerX += playerDirSin * PLAYER_MOVEMENT_SPEED * deltaT * currentSpeed;
	playerY += playerDirCos * PLAYER_MOVEMENT_SPEED * deltaT * currentSpeed;

	if(inputState->isKeyPressed('D'))
	{
		booster1X = 0.9;
		booster2X = -0.2;
		rotateZ -= rotationSpeed * deltaT;
		spriteX = 1;
		booster1Y = -2.3;

	}
	 else if(inputState->isKeyPressed('A'))
	{
		rotateZ += rotationSpeed * deltaT;
		spriteX = 0.666666;
		booster1X = -0.9;
		booster2X = 0.2;
		booster1Y = -2.3;
	}
	 else {
		 booster1X = -0.7;
		 booster2X = 0.5;
		 spriteX = 0.33333333333;
		 booster1Y = booster2Y = -2.6;
	 }
	//**************************************ATTACK AND BOOST
	if (boostOn == true) {
		maxSpeed = boostSpeed;
	}

	if (boostOn == false) {
		maxSpeed = defaultMaxSpeed;

		if (currentSpeed > maxSpeed) {
			currentSpeed -= 0.1;
		}
	}

	//***************************************JUMPING
	if (inputState->isKeyPressed('J'))
	{
		jump = true;
	}
	if ( jump == true) //is jumping
	{
		if ( jumpStage < JUMP_HEIGHT) //is before apex
		{
			if (falling == false) //is going up
			{
				jumpStage = jumpStage + 0.002 + (1 * deltaT);
				if ( jumpStage  > JUMP_HEIGHT - 0.5)
				{
					falling = true;
				}
			}
			
			else if (falling == true) //is coming back down
			{
				jumpStage = jumpStage - 0.003 - (1 * deltaT);
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
		if (powerORBSize < powerORBMaxSize) {
			powerORBSize += 0.001 + (1 * deltaT);
		}
	}
	else if(powerORBOn == false) {
		if (powerORBSize > 0.0) {
			powerORBSize -= 0.001 + (1 * deltaT);
		}
		if (powerORBSize == 0.0) {
			powerORBRotate = 0.0;
		}
	}
	
	shieldTime += (SHIELD_OSCILATION_SPEED * deltaT );

	if (shieldOn == true) {
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

	//****************************************RESPAWN/DEATH STATE
	if (respawnState == true) {
		respawnTimer += 0.1;
		if (respawnTimer > RESPAWN_STATE_TIME) {
			respawnState = false;
			respawnTimer = 0.0;
			respawnstateOpacity = 1.0;
		}
		else {
			respawnstateOpacity = 0.4;
		}
	}

	//****************************************MATRIX COLLISION
	setTraMat(mb1, playerX, playerY, 0.0);
	setRotMat(mb2, M_PI*rotateZ / 180.0, 2);
	MultMat(mb1, mb2, mb);
	for (int i = 0; i < 4; ++i) {
		MultMatPre2DPoint(mb, &playerPoly.vert[i], &playerPolyN.vert[i]);
	}
}

void PlayerShip::render()
{
	glPushMatrix();
		glTranslated(playerX, playerY, 0.0);
		glRotated(rotateZ, 0.0, 0.0, 1);
		glScaled(jumpStage, jumpStage, 3.0);

		glBindTexture(GL_TEXTURE_2D, playerTextureID);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

		glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 1.0, 1.0f, respawnstateOpacity);

		glTexCoord2f(spriteX - 0.3333, 0);
		glVertex2f(-2, -2);//bottom left

		glTexCoord2f(spriteX, 0);
		glVertex2f(2, -2);//bottom right

		glTexCoord2f(spriteX - 0.333, 1);
		glVertex2f(-2, 4);//top left

		glTexCoord2f(spriteX, 0);
		glVertex2f(2, -2);//bottom right

		glTexCoord2f(spriteX, 1);
		glVertex2f(2, 4);//top right

		glTexCoord2f(spriteX - 0.3333, 1);
		glVertex2f(-2, 4);//top left
		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);


		float fscale = (1 + sin(shieldTime * 20) / 10.0f) * (rocketFlamesScaleY - 0.2);
		//Booster 1
		glPushMatrix();
			
			glTranslated(booster1X, booster1Y,0.0);
			glScaled(fscale, fscale, 1.0);

			glBindTexture(GL_TEXTURE_2D, rocketBooster);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_TRIANGLES);
	
				glColor3f(boosterR, boosterG, boosterB);

				glTexCoord2f(0, 0);
				glVertex2f(-0.6, -1);

				glTexCoord2f(1, 0);
				glVertex2f(0.6, -1);

				glTexCoord2f(0, 1);
				glVertex2f(-0.6, 1);

				glTexCoord2f(1, 0);
				glVertex2f(0.6, -1);

				glTexCoord2f(1, 1);
				glVertex2f(0.6, 1);

				glTexCoord2f(0, 1);
				glVertex2f(-0.6, 1);
			glEnd();

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//Booster 2
		glPushMatrix();
			
		glTranslated(booster2X, booster2Y, 0.0);
			glScaled(fscale, fscale, 1.0);

			glBindTexture(GL_TEXTURE_2D, rocketBooster);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_TRIANGLES);
				glColor3f(boosterR, boosterG, boosterB);

				glTexCoord2f(0, 0);
				glVertex2f(-0.6, -1);

				glTexCoord2f(1, 0);
				glVertex2f(0.6, -1);

				glTexCoord2f(0, 1);
				glVertex2f(-0.6, 1);

				glTexCoord2f(1, 0);
				glVertex2f(0.6, -1);

				glTexCoord2f(1, 1);
				glVertex2f(0.6, 1);

				glTexCoord2f(0, 1);
				glVertex2f(-0.6, 1);
			glEnd();

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		//***********************************************************POWERUP SPIKEBALL 

		glPushMatrix();
			glScaled(powerORBSize, powerORBSize, 1.0);
			glTranslated(0.0, powerORBTranslateY, 0.0);
			glRotated(powerORBRotate, 0.0, 0.0, 1);

			glBindTexture(GL_TEXTURE_2D, spikeBallTextureID);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		
		//*************************************************SHEILD
		glPushMatrix();
			float scale = (2 + sin(shieldTime * 4) / 5.0f) * shieldScale;

			glScaled(scale, scale, 1.0);

			glBindTexture(GL_TEXTURE_2D, shieldTextureID);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 1.0f, 1.0f);

			glTexCoord2f(0, 0);
			glVertex2f(-1.5, -1.8);

			glTexCoord2f(1, 0);
			glVertex2f(1.5, -1.8);

			glTexCoord2f(0, 1);
			glVertex2f(-1.5, 2.8);

			glTexCoord2f(1, 0);
			glVertex2f(1.5, -1.8);

			glTexCoord2f(1, 1);
			glVertex2f(1.5, 2.8);

			glTexCoord2f(0, 1);
			glVertex2f(-1.5, 2.8);
			glEnd();

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		
	glPopMatrix();
}

void PlayerShip::setPlayerJumpOn() {
	jump = true;
}

void PlayerShip::setBlackHoleSlowOn() {
	if (currentSpeed > 2) {
		currentSpeed = currentSpeed - 0.3;
	}
	else if (currentSpeed < -2) {
		currentSpeed = currentSpeed + 0.3;
	}

}

double PlayerShip::getPlayerRot() {
	return rotateZ;
}

double PlayerShip::getPlayerX() {
	return playerX;
}

double PlayerShip::getPlayerY() {
	return playerY;
}

double PlayerShip::getCollisionWait() {
	return collisionWait;
}

bool PlayerShip::checkShouldColide() {

	if (respawnState == true || jump == true) {
		return true;
	}
	return false;
}

void PlayerShip::incrementCollisionWait() {
	collisionWait++;
}

void PlayerShip::shieldToggle() {
	if (!shieldOn) {
		shieldScale = 0.0;
		shieldTime = 0.0;
		shieldOn = true;
	}
	else {
		shieldOn = false;
	}
}

void PlayerShip::powerBallToggle() {
	powerORBOn = !powerORBOn;
}

void PlayerShip::setRespawnState() {
	respawnState = true;
	currentSpeed = 0; 
	if (lives > 0) {
		lives--;
	}
}

int PlayerShip::getLivesCount() {
	return lives;
}

void PlayerShip::boostToggleOn()
{
	boostOn = true;
	boosterR = 0.0;
	boosterG = 1.0;
	boosterB = 0.0;
}

void PlayerShip::boostToggleOff()
{
	boostOn = false;
	boosterR = 1.0;
	boosterG = 1.0;
	boosterB = 1.0;
}

polygon PlayerShip::getPolygonN()
{
	return playerPolyN;
}