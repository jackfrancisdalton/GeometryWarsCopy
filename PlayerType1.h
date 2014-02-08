#include <gl/gl.h>			

class PlayerType1 
{
private:
	GLuint playerTextureID, spikeBallTextureID, shieldTextureID, shieldHitTextureID;
	double playerX;
	double playerY;
	double rotateZ;
	bool boostOn;
	double jumpStage;
	bool falling;
	bool jump;
	double maxSpeed;
	double acceleration;
	double shieldTime;
	double powerORBRotate;
	double attackZ;
	bool powerORBOn;
	double powerORBSize;
	bool shieldOn;
	double shieldScale;
	double powerORBTranslateY;

public:
	PlayerType1();

	virtual void initialise();											// Called on application start up
	virtual void shutdown();											// Called on application shut down

	virtual void onSwitchIn();											// Activity switch in; called when the activity changes and this one switches in
	//virtual void onReshape(int width, int height);						// called when the window is resized
	virtual void update(double deltaT, double prevDeltaT, InputState *inputState);
	virtual void render();												// Render function

	virtual void onKeyUp(int key);										// Called when key released
};
