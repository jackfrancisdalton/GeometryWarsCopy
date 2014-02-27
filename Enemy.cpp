#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "Enemy.h"
#include <random>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)

Enemy::Enemy()
{
}

void Enemy::initialise(){}

double Enemy::getEnemyRot() {
	return rot;
}

double Enemy::getEnemyX() {
	return posX;
}

double Enemy::getEnemyY() {
	return posY;
}

void Enemy::shutdown()
{
	glDeleteTextures(1, &enemyTextureId);
}

void Enemy::onSwitchIn()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Enemy::update(double deltaT, double prevDeltaT, double playerX, double playerY){}

void Enemy::render(){}
