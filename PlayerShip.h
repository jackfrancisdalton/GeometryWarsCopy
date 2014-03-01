#include <gl/gl.h>			

class PlayerShip
{
private:
	GLuint playerTextureID, rocketBooster, spikeBallTextureID, shieldTextureID, shieldHitTextureID;
	double playerX;
	double playerY;
	double rotateZ;
	bool boostOn;
	double jumpStage;
	bool falling;
	bool jump;
	double shieldTime;
	double powerORBRotate;
	double attackZ;
	bool powerORBOn;
	double powerORBSize, powerORBMaxSize;
	bool shieldOn;
	double shieldScale;
	double powerORBTranslateY;
	double rotationSpeed;
	double maxSpeed, defaultMaxSpeed, boostSpeed;
	double currentSpeed, acceleration, decceleration;
	int shipChoice;
	double rocketFlamesScaleY;
	double rocketFlamesScaleX;
	double HitRadius;

public:
	PlayerShip();
	PlayerShip(int shipID);

	virtual void powerBallToggle();
	virtual void boostToggle();
	virtual void shieldToggle();
	virtual double getPlayerRot();
	virtual double getPlayerX();
	virtual double getPlayerY();
	virtual void initialise();											// Called on application start up
	virtual void shutdown();											// Called on application shut down
	virtual void onSwitchIn();											// Activity switch in; called when the activity changes and this one switches in
	virtual void update(double deltaT, double prevDeltaT, InputState *inputState);
	virtual void render();												// Render function
};
