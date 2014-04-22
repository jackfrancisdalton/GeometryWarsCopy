#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <gl/gl.h>			
#include "PolyObjects.h"
#include "Matrix.h"

class Collectable
{
protected:
	GLuint collectableTextureId;
	double posX, posY, rot;
	double size, height, width;
	polygon objectPoly, objectPolyN;

public:
	Collectable();
	polygon getPolygonN();
};

#endif 