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


HUD::HUD()
{
	font = CreateFont(-40,							// Height Of Font
		0,								// Width Of Font
		0,								// Angle Of Escapement
		0,								// Orientation Angle
		FW_NORMAL,						// Font Weight
		FALSE,							// Italic
		FALSE,							// Underline
		FALSE,							// Strikeout
		ANSI_CHARSET,					// Character Set Identifier
		OUT_TT_PRECIS,					// Output Precision
		CLIP_DEFAULT_PRECIS,			// Clipping Precision
		ANTIALIASED_QUALITY,			// Output Quality
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
		"Arial");					// Font Name

	base = glGenLists(96);

}


void HUD::initialise()
{
	HDC			hDC = NULL;		// Private GDI Device Context
	healthIconTextureID = SOIL_load_OGL_texture("health_icon.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	wglUseFontBitmaps(hDC, 32, 96, base);
}

void HUD::setPosition(double x, double y) {
	posX = x;
	posY = y;
}

void HUD::glutBitmapCharacter(void *font, int character) {

}

void HUD::shutdown()
{
	
}

void HUD::update(double deltaT, double prevDeltaT, InputState *inputState)
{
}

void HUD::render()
{
	//glPrint("Bitmap Text fififi A Number: ");
	//*******************************HUD HEART 1
	glPushMatrix();
	glTranslated(posX-6, posY+3, 1.0);
	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);
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

	//*******************************HUD HEART 2
	glPushMatrix();
	glTranslated(posX - 4, posY + 3, 1.0);
	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);
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

	//*******************************HUD HEART 3
	glPushMatrix();

	glTranslated(posX - 2, posY + 3, 1.0);
	glBindTexture(GL_TEXTURE_2D, healthIconTextureID);
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
}


void HUD::glPrint(std::string str)					// Custom GL "Print" Routine
{
	std::stringstream stream;
	stream << str << " " << 0;

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(stream.str().size(), GL_UNSIGNED_BYTE, stream.str().c_str());	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}
