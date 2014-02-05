//
// The structure of the Graphics 1 OpenGL template is explained in README.txt
//

/*
GameActivity implementation


The comments in the file Activity.cpp give a little more info about each method

This activity is where the main game logic goes.
Most of your game code will go here
*/


#include <windows.h>		// Header File For Windows
#include <gl\gl.h>		// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <algorithm>
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"			// Needed to access member functions and variables from OpenGLApplication
#include "GameActivity.h"

#define VIEW_SIZE 30.0					// The height of the view in WORLD SPACE
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

GameActivity::GameActivity(OpenGLApplication *app)
	: Activity(app)		// Call super constructor
{
	// Initialse camera and player positions to be a the origin
	camX = camY = 0.0;
	playerX = playerY = 0.0;
	rotateZ = 0.0;
	attackZ = 0.0;
	acceleration = 0.0;
	jump = false;
	falling = false;
	jumpStage = 1.0;
	powerORBRotate = 0.0;
	powerORBTranslateY = 2.0;
	powerORBOn = false;
	powerORBSize = 0.0;
	shieldScale = 0.0;
	shieldTime = 0.0;
	shieldOn = false;
	boostOn = false;
	maxSpeed = 5;
}



/*
*
* ACTIVITY METHODS
* Put your application/game code here
*
*/
void GameActivity::initialise()
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

		healthIconTextureID = SOIL_load_OGL_texture("health_icon.png",		
		SOIL_LOAD_AUTO,							 
		SOIL_CREATE_NEW_ID,										
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}


void GameActivity::shutdown()
{
	glDeleteTextures(1, &playerTextureID);
}



void GameActivity::onSwitchIn()
{
	glClearColor(0.0,0.0,0.0,0.0);						//sets the clear colour to black
}

void GameActivity::onReshape(int width, int height)
{
	// If you need to do anything when the screen is resized, do it here

	// EXAMPLE CODE
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	double aspect = app->getAspectRatio();
	// The height of the visible area is defined by VIEW_SIZE. Split it half each way around the origin, hence the *0.5
	// Take the aspect ratio into consideration when computing the width of the visible area
	gluOrtho2D(-VIEW_SIZE*0.5*aspect, VIEW_SIZE*0.5*aspect,  -VIEW_SIZE*0.5, VIEW_SIZE*0.5);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void GameActivity::update(double deltaT, double prevDeltaT)
{
	// Update the application; if the current frame is frame number F, then the previous frame is F-1 and the one before that is F-2
	// deltaT is the time elapsed from frame F-1 to frame F, prevDeltaT is the time elapsed from F-2 to F-1

	// Update the simulation here
	// TRY NOT TO DO ANY RENDERING HERE
	// step the simulation forward by the amount of time specified by deltaT
	//
	// If you need to do different things depending on whether or not keys are pressed, etc,
	// get the member variable inputState and use its isKeyPressed(), getMouseX(), getMouseY() and isMouseButtonPressed() methods
	// to determine the state of the keys


	// Arrow keys control camera
	// NOTE the use of deltaT here; we move the position of the camera by the SPEED * deltaT


	if(inputState->isKeyPressed(VK_LEFT))
	{
		camX -= CAMERA_MOVEMENT_SPEED * deltaT;
	}
	if(inputState->isKeyPressed(VK_RIGHT))
	{
		camX += CAMERA_MOVEMENT_SPEED * deltaT;
	}
	if(inputState->isKeyPressed(VK_UP))
	{
		camY += CAMERA_MOVEMENT_SPEED * deltaT;
	}
	if(inputState->isKeyPressed(VK_DOWN))
	{
		camY -= CAMERA_MOVEMENT_SPEED * deltaT;
	}

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

void GameActivity::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// Reset The Modelview Matrix
	// Use the negated camera position as a translation; effectively we move the world and the camera so that the camera is at 0,0,0

	//*******************************HUD ORB1
	glPushMatrix();
	
	glTranslated(12.0, -13.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);

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

	//*******************************HUD ORB2
	glPushMatrix();
	
	glTranslated(14.0, -13.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);

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

	//*******************************HUD ORB3
	glPushMatrix();
	
	glTranslated(16.0, -13.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);
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

	glRotated(-rotateZ,0.0, 0.0, 1);
	glTranslated(-playerX, -playerY, 0.0);

	renderDebugGrid(-100.0, -100.0, 400.0, 400.0, 30, 30);

	//***********************************************************STATIONARY ORB
	glPushMatrix();
	glTranslated(0.0, 3.0, 0.9);

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

	//********************************************************BACKGROUND
	glBindTexture(GL_TEXTURE_2D, playerTextureID);
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

	//***********************************************************PLAYER
	glPushMatrix();
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
		//*/
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

	glFlush();
}



void GameActivity::onMouseDown(int button, int mouseX, int mouseY)
{
	// This method will be invoked when a mouse button is pressed
	// button: 0=LEFT, 1=MIDDLE, 2=RIGHT
	// mouseX and mouseY: position
}

void GameActivity::onMouseUp(int button, int mouseX, int mouseY)
{
	// This method will be invoked when a mouse button is released
	// button: 0=LEFT, 1=MIDDLE, 2=RIGHT
	// mouseX and mouseY: position
}

void GameActivity::onMouseMove(int mouseX, int mouseY)
{
	// This method will be invoked when the mouse is moved
	// mouseX and mouseY: position
}

void GameActivity::onKeyDown(int key)
{
	if(key == '2') 
	{
		attackZ += PLAYER_ROTATION_SPEED;
	}
}

void GameActivity::onKeyUp(int key)										// Called when key released
{
	if (key == VK_F1)
	{
		// F1; switch to end screen activity
		app->setCurrentActivity(app->endScreen);
	}
	else if(key == '1') {
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
	if(key == VK_RETURN) {

		app->setCurrentActivity(app->pauseScreen);
	}
}

void GameActivity::chooseWizardCharacter()
{
}

void GameActivity::chooseWarriorCharacter()
{
}

void GameActivity::renderDebugGrid(float left, float bottom, float width, float height, int hSegments, int vSegments)
{
	// Render a grey grid using lines
	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_LINES);

	// Vertical lines
	float dx = width / hSegments;
	float x = left;
	for (int i = 0; i <= hSegments; i++)
	{
		glVertex2f(x, bottom);
		glVertex2f(x, bottom + height);

		x += dx;
	}
	
	// Horizontal lines
	float dy = height / vSegments;
	float y = bottom;
	for (int i = 0; i <= hSegments; i++)
	{
		glVertex2f(left, y);
		glVertex2f(left + width, y);

		y += dy;
	}

	glEnd();
}

