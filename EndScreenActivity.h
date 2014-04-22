#include <gl/gl.h>			
#include "Activity.h"

class EndScreenActivity : public Activity
{
private:
	GLuint textureID;

public:
	EndScreenActivity(OpenGLApplication *app);
	virtual void initialise();										
	virtual void shutdown();											
	virtual void onSwitchIn();											
	virtual void onReshape(int width, int height);						
	virtual void render();												
	virtual void onKeyUp(int key);								
};
