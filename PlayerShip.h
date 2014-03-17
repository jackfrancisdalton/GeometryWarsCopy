#include <gl/gl.h>	
#include "PolyObjects.h"
#include "Matrix.h"

class PlayerShip
{
private:
	GLuint playerTextureID, rocketBooster, spikeBallTextureID, shieldTextureID, shieldHitTextureID;
	int lives;

	double playerX;
	double playerY;
	double rotateZ;

	//MOVMENT
	double rotationSpeed;
	double currentSpeed, maxSpeed, defaultMaxSpeed, boostSpeed;
	double acceleration, decceleration;
	double directionChangeSpeed;

	//TOGGLES
	bool boostOn;
	bool powerORBOn;
	bool shieldOn;
	bool respawnState;

	//JUMP
	double jumpStage;
	bool falling;
	bool jump;

	//SHIELD
	double shieldTime;
	double shieldScale;
	double shieldTimeLength;
	double shieldTimeMax;

	//POWER ORB
	double powerORBRotate;
	double powerORBSize, powerORBMaxSize;
	double powerORBTranslateY;
	
	//RESPAWN SATE
	double respawnTimer;
	double respawnstateOpacity;
	bool deadState;
	double deadStateTime;
	
	//VISUAL
	int shipChoice;
	double rocketFlamesScaleY;
	double rocketFlamesScaleX;
	float boosterR, boosterG, boosterB;
	double spriteX, spriteY;
	double booster1X = 0.8;
	double booster2X = 0.8;
	double booster1Y, booster2Y = -2.6;
	double boosterOpacity;

	//COLLISION
	polygon playerPoly, playerPolyN;
	float mb[16], mb1[16], mb2[16];
	double collisionWait;
	double wallMaxX = 67;
	double wallMaxY = 67;
	double wallMinX = -75;
	double wallMinY = -75;


public:
	PlayerShip();
	PlayerShip(int shipID);

	virtual void powerBallToggle();
	virtual void boostToggleOn();
	virtual void boostToggleOff();
	virtual void shieldToggleOn();

	virtual void setRespawnState();
	virtual void setPlayerJumpOn();
	virtual void setBlackHoleSlowOn();
	virtual void setDeadState(bool val);
	virtual void setDeadStateTime(double val);
	virtual bool checkShouldColide();

	virtual bool getDeadState();
	virtual double getDeadStateTime();
	virtual double getPlayerRot();
	virtual double getPlayerX();
	virtual double getPlayerY();
	virtual bool getShieldState();
	virtual bool getJumpState();
	virtual polygon getPolygonN();
	virtual int getLivesCount();
	virtual double getCollisionWait();
	virtual void wallCollisionHandeling();

	virtual void incrementCollisionWait();
	virtual void initialise();											
	virtual void shutdown();											
	virtual void onSwitchIn();											
	virtual void update(double deltaT, double prevDeltaT, InputState *inputState);
	virtual void render();												
};
