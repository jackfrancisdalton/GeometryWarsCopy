#include <windows.h>		// Header File For Windows
#include <gl\gl.h>		// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <algorithm>
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"			// Needed to access member functions and variables from OpenGLApplication
#include "GameActivity.h"
#include <iostream>
#include <vector>


#define MAP_SIZEX 10
#define MAP_SIZEY 10
#define VIEW_SIZE 80.0
#define CAMERA_MOVEMENT_SPEED 10.0
#define PLAYER_MOVEMENT_SPEED 10.0
#define JUMP_HEIGHT 2.5
#define SHIELD_OSCILATION_SPEED 1.5
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)
#define SHIELD_GROWTH_RATE 1.0

char map[20][20] = {
	{ 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 },
};

GameActivity::GameActivity(OpenGLApplication *app): Activity(app)	
{
	camX = camY = camRot = 0.0;
	int skinID = 0;
	mainHUD = HUD();
	mapWidth = 20;
	mapHeight = 20;
}

void GameActivity::initialise()
{
	vertWall = SOIL_load_OGL_texture("vert-wall.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	horzWall = SOIL_load_OGL_texture("horz-wall.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	cornerWall = SOIL_load_OGL_texture("corner-wall.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	spaceTextureID = SOIL_load_OGL_texture("space-texture.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	mainHUD.initialise();

	//matrixFiller(*map, 20, 20);

	for (int i = 0; i < 20; i++) {
		EnemyType1* e = new EnemyType1();
		enemyList.push_back(e);
	}

	for (int i = 0; i < 10; i++) {
		EnemyType2* g = new EnemyType2();
		enemyList.push_back(g);
	}

	for (int i = 0; i < 20; i++) {
		EnemyType3* g = new EnemyType3();
		enemyList.push_back(g);
	}

	for each (EnemyType1* var in enemyList)
	{
		var->initialise();
	}
}

void GameActivity::shutdown()
{
	glDeleteTextures(1, &healthIconTextureID);
}

void GameActivity::onSwitchIn()
{
	glClearColor(0.0,0.0,0.0,0.0);						//sets the clear colour to black
	player = PlayerShip(chosenShipID);
	player.initialise();
}

void GameActivity::onReshape(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	aspect = app->getAspectRatio();
	gluOrtho2D(-VIEW_SIZE*0.5*aspect, VIEW_SIZE*0.5*aspect,  -VIEW_SIZE*0.5, VIEW_SIZE*0.5);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	mainHUD.setPosition(VIEW_SIZE*0.5*aspect, -VIEW_SIZE*0.5);
}

void GameActivity::update(double deltaT, double prevDeltaT)
{
	player.update(deltaT, prevDeltaT, inputState);
	camRot = player.getPlayerRot();
	camX = player.getPlayerX();
	camY = player.getPlayerY();
	for each (Enemy* var in enemyList)
	{
		var->update(deltaT, prevDeltaT, camX, camY);
	}
}

void GameActivity::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	mainHUD.render();
	glRotated(-camRot,0.0, 0.0, 1);
	glTranslated(-camX, -camY, 0.0);
	//renderDebugGrid(-100.0, -120.0, 400.0, 400.0, 30, 30);
	
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			drawSquare(i, j, map[i][j]);
		}
	}
	
	for each (EnemyType1* var in enemyList)
	{
		var->render();
	}
	player.render();
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
	if (key == VK_F1)
	{
		app->setCurrentActivity(app->endScreen);
	}
	else if (key == VK_RETURN) {

		app->setCurrentActivity(app->pauseScreen);
	}
	else if (key == '1') {
		player.shieldToggle();
	}
	else if (key == '2') {
		player.powerBallToggle();
	}
	else if (key == '3') {
		player.boostToggle();
	}
}

void GameActivity::onKeyUp(int key)									
{
}


void GameActivity::renderDebugGrid(float left, float bottom, float width, float height, int hSegments, int vSegments)
{
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
/*
void GameActivity::matrixFiller(char *map, int w, int h)
{
	int i, j;

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (j == 0 || j == w) {
				map[i][j] = 1;
			}
			else if (i == 0 || j == h){
				map[i][j] = 2;
			}
			else {
				map[i][j] = 0;
			}
		}
	}
}
*/

void GameActivity::drawSquare(double posX, double posY, GLuint mapId) {
	glPushMatrix();

	glTranslated(posX * 8 - (10 * 8), posY * 8 - (10 * 8), 0.0);
	
	if (mapId == 3) {
		glBindTexture(GL_TEXTURE_2D, cornerWall);
	}
	else if (mapId == 1){
		glBindTexture(GL_TEXTURE_2D, vertWall);
	}
	else if (mapId == 2){
		glBindTexture(GL_TEXTURE_2D, horzWall);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, spaceTextureID);
	}
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0, 0);
	glVertex2f(-4, -4);//bottom left

	glTexCoord2f(1.0, 0);
	glVertex2f(4, -4);//bottom right

	glTexCoord2f(0.0, 1.0);
	glVertex2f(-4, 4);//top left

	glTexCoord2f(1.0, 0);
	glVertex2f(4, -4);//bottom right

	glTexCoord2f(1.0, 1.0);
	glVertex2f(4, 4);//top right

	glTexCoord2f(0.0, 1.0);
	glVertex2f(-4, 4);//top left
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}