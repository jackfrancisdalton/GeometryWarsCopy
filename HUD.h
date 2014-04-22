#include <gl/gl.h>			
#include <string>
#include <sstream>
#include "glfont2.h"

class HUD
{

private:
	GLuint healthIconTextureID;
	double posX, posY, rot, texY1, texY2;
	double gameTime;
	std::string SgameTime;
	bool gamePaused;
	int score;
	GLuint base;
	glfont::GLFont HUDFont;
	GLuint FONTTEXTURE;

public:
	HUD();
	HUD(double x, double y);
	virtual void glPrint(std::string str);
	//virtual void getGameTime();
	virtual void decreaseHealthTexture();
	virtual void increaseHealthTexture();
	virtual void initialise();											// Called on application start up
	virtual void shutdown();											// Called on application shut down
	virtual void update(double deltaT, double prevDeltaT, InputState *inputState);
	virtual void render();												// Render function
	virtual void setPosition(double posX, double posY);
	void glutBitmapCharacter(void *font, int character);
};
