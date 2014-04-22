#include <gl/gl.h>			

#include "Activity.h"

class PauseScreenActivity : public Activity
{
private:
	GLuint textureID;

public:
	PauseScreenActivity(OpenGLApplication *app);

	// ACTIVITY METHODS
	virtual void initialise();											// Called on application start up
	virtual void shutdown();											// Called on application shut down

	virtual void onSwitchIn();											// Activity switch in; called when the activity changes and this one switches in
	virtual void onReshape(int width, int height);						// called when the window is resized
	virtual void render();												// Render function

	virtual void onKeyDown(int key);										// Called when key released
};
