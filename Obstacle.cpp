#include <windows.h>		
#include <gl/gl.h>			
#include <gl/glu.h>		
#include <math.h>
#include "SOIL.h"
#include "OpenGLApplication.h"		
#include "Obstacle.h"
#include <random>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#define DEG_2_RAD(x) (x * M_PI / 180.0)

Obstacle::Obstacle(){}

void Obstacle::shutdown()
{
	glDeleteTextures(1, &TextureId);
}

void Obstacle::onSwitchIn()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
