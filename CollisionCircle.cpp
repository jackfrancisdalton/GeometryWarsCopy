#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "CollisionCircle.h"
#include <random>
#include <iostream>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)

CollisionCircle::CollisionCircle() {
}

CollisionCircle::CollisionCircle(double posX, double posY)
{
	radius = 5;
	centreX = posX;
	centreY = posY;
}

void CollisionCircle::Update(double posX, double posY) {
	centreX = posX;
	centreY = posY;
}

double CollisionCircle::getX() {
	return centreX;
}

double CollisionCircle::getY() {
	return centreY;
}

bool CollisionCircle::isColidingWith(CollisionCircle &other){
	
	if ((pow((centreY - other.centreY),2.0)) + (pow((centreX - other.centreX),2.0)) < (pow((radius + other.radius),2.0)))
	{
		return true;
	}
	return false;
}