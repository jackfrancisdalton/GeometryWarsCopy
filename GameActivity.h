#pragma once
#include "Activity.h"
#include "PlayerType1.h"

class GameActivity : public Activity
{
private:
	double camX, camY;
	GLuint healthIconTextureID, playerTextureID;
	double playerX_spriteSheet_offset, playerY_spriteSheet_offset;
	double rotateZ;
	double playerX;
	double playerY;
	PlayerType1 player;

public:
	GameActivity(OpenGLApplication *app);
	virtual void initialise();											// Called on application start up
	virtual void shutdown();											// Called on application shut down

	virtual void onSwitchIn();											// Activity switch in; called when the activity changes and this one switches in
	virtual void onReshape(int width, int height);						// called when the window is resized
	virtual void update(double deltaT, double prevDeltaT);				// Update the application; if the current frame is frame number F, then the previous frame is F-1 and the one before that is F-2
																		// deltaT is the time elapsed from frame F-1 to frame F, prevDeltaT is the time elapsed from F-2 to F-1
	virtual void render();												// Render function

	virtual void onMouseDown(int button, int mouseX, int mouseY);		// Called when mouse button pressed
	virtual void onMouseUp(int button, int mouseX, int mouseY);			// Called when mouse button released
	virtual void onMouseMove(int mouseX, int mouseY);					// Called when mouse moved
	virtual void onKeyDown(int key);									// Called when key pressed
	virtual void onKeyUp(int key);										// Called when key released


	void chooseWizardCharacter();
	void chooseWarriorCharacter();


	// Drawing a grid in the background; useful for debugging
	void renderDebugGrid(float left, float bottom, float width, float height, int hSegments, int vSegments);
};