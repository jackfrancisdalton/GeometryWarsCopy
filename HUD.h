#include <gl/gl.h>			
#include <string>
#include <sstream>

class HUD
{

private:
	GLuint healthIconTextureID;
	double posX, posY;
	HFONT font;
	GLuint base;

public:
	HUD();
	virtual void glPrint(std::string str);
	virtual void initialise();											// Called on application start up
	virtual void shutdown();											// Called on application shut down
	virtual void update(double deltaT, double prevDeltaT, InputState *inputState);
	virtual void render();												// Render function
	virtual void setPosition(double posX, double posY);
	void glutBitmapCharacter(void *font, int character);
};
