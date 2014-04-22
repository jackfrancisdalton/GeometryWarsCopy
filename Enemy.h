#ifndef ENEMY_H
#define ENEMY_H

#include <gl/gl.h>			
#include "PolyObjects.h"
#include "Matrix.h"
#include <time.h>

class Enemy
{
protected:
	GLuint enemyTextureId;
	int health;
	double posX, posY, rot;
	float textureX, textureY;
	int refreshWait, refreshIndex;
	int frameCounter;
	double speed, defaultSpeed;
	polygon enemyPoly, enemyPolyN;
	double enemySize = 1;
	int id;
	bool blackHoleCollsion;
	bool deadState;

public:
	Enemy();
	virtual void setSpeed(double speed);
	virtual double getEnemyRot();
	virtual double getEnemyX();
	virtual double getEnemyY();
	virtual double getDefaultSpeed();
	virtual double getSpeed();
	virtual bool getDeadState();
	virtual void setDeadState();
	virtual polygon getPolygonN();
	virtual void initialise() = 0;		
	virtual void BlackHoleCollisionOn();
	virtual void BlackHoleCollisionOff();
	virtual void shutdown();											
	virtual void onSwitchIn();											
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY) = 0;
	virtual void render() = 0;	
	virtual int getId();
};

#endif