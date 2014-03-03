#ifndef ENEMY_H
#define ENEMY_H

#include <gl/gl.h>			
#include <CollisionCircle.h>	

class Enemy
{
protected:
	GLuint enemyTextureId;
	int health;
	bool collisionState;
	double posX, posY, rot;
	float textureX, textureY;
	int refreshWait, refreshIndex;
	int frameCounter;
	double speed;
	CollisionCircle collisionCircle;

public:
	Enemy();
	virtual double getEnemyRot();
	virtual double getEnemyX();
	virtual double getEnemyY();
	virtual void setEnemyCollisionState(bool state);
	virtual CollisionCircle getCollisionCircle();
	virtual CollisionCircle& getCollisionCircleReference();
	virtual void initialise() = 0;											// Called on application start up
	virtual void shutdown();											// Called on application shut down
	virtual void onSwitchIn();											// Activity switch in; called when the activity changes and this one switches in
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY) = 0;
	virtual void render() = 0;												// Render function
};

#endif