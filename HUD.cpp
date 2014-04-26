#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "HUD.h"
#include <string>		
#include <sstream>


#define VIEW_SIZE 50.0
#define CAMERA_MOVEMENT_SPEED 10.0
#define PLAYER_MOVEMENT_SPEED 10.0
#define ROTATION_SPIKE_BALL_SPEED 500.0
#define JUMP_HEIGHT 2.5
#define SHIELD_OSCILATION_SPEED 1.5
#define SHIELD_GROWTH_RATE 1.0
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)

using namespace glfont;

HUD::HUD(double x, double y)
{
	posX = x;
	posY = y;
	texY1 = 1.0;
	texY2 = 0.8;
	SgameTime = "";
	Sscore = "";
	MainMessage = "";
	PopUpMessage = "";
}

HUD::HUD(){}

void HUD::initialise()
{
	healthIconTextureID = SOIL_load_OGL_texture("health_bar_sprite.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	gameTime = 0;

	glGenTextures(1, &FONTTEXTURE);
	HUDFont.Create("Arial.glf", FONTTEXTURE);
}

void HUD::setPosition(double x, double y) {
	posX = x;
	posY = y;
}

void HUD::setPopUpMessage(std::string message) {
	PopUpMessage = message;
}

void HUD::setMainMessage(std::string message) {
	MainMessage = message;
}


void HUD::increaseHealthTexture()
{
	if (texY1 < 0.9)
	{
		texY1 = texY1 + 0.2;
		texY2 = texY2 + 0.2;
	}
}

void HUD::decreaseHealthTexture()
{
	if (texY2 > 0.1)
	{
		texY1 = texY1 - 0.2;
		texY2 = texY2 - 0.2;
	}
}

void HUD::glutBitmapCharacter(void *font, int character) {

}

void HUD::shutdown()
{
	
}

void HUD::update(double deltaT, double prevDeltaT, InputState *inputState, int score)
{
	gameTime += 2 * deltaT;
	std::ostringstream strs;

	if (((int)(gameTime / 60) % 60) < 10)
	{
		strs << "0";
		strs << (int)(gameTime / 60) % 60;
	}
	else
	{
		strs << (int)(gameTime / 60) % 60;
	}

	strs << ":";

	if (((int)gameTime % 60) < 10)
	{
		strs << "0";
		strs << (int)gameTime % 60;
	}
	else
	{
		strs << (int)gameTime % 60;
	}
	SgameTime = strs.str();

	std::ostringstream strs2;
	strs2 << "Score: ";
	strs2 << score;
	Sscore = strs2.str();
}

void HUD::render()
{
	glPushMatrix();
	glLoadIdentity();
	glTranslated(posX - 16.0, posY + 5.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0, texY1);
	glVertex2f(-14, -4);

	glTexCoord2f(1, texY1);
	glVertex2f(14, -4);

	glTexCoord2f(0, texY2);
	glVertex2f(-14, 4);

	glTexCoord2f(1, texY1);
	glVertex2f(14, -4);

	glTexCoord2f(1, texY2);
	glVertex2f(14, 4);

	glTexCoord2f(0, texY2);
	glVertex2f(-14, 4);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
		glLoadIdentity();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		HUDFont.Begin();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		HUDFont.DrawString(SgameTime, 0.2f, -7.0f, 40.0f);
		glDisable(GL_BLEND);
	glPopMatrix();


	glPushMatrix();
		glLoadIdentity();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		HUDFont.Begin();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		HUDFont.DrawString(Sscore, 0.2f, -20.0f, -20.3f);
		glDisable(GL_BLEND);
	glPopMatrix();

	glPushMatrix();
		glLoadIdentity();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		HUDFont.Begin();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		HUDFont.DrawString(PopUpMessage, 0.1f, -20.0f, -10.3f);
		glDisable(GL_BLEND);
	glPopMatrix();

	glPushMatrix();
		glLoadIdentity();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		HUDFont.Begin();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		HUDFont.DrawString(MainMessage, 0.2f, -10.0f, 0.0f);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void HUD::glPrint(std::string str)						// Custom GL "Print" Routine
{
	std::stringstream stream;
	stream << str << " " << 0;

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(stream.str().size(), GL_UNSIGNED_BYTE, stream.str().c_str());	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}
