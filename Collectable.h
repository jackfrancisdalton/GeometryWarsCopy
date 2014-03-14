#ifndef OBJECT_H
#define OBJECT_H

#include <gl/gl.h>			
#include "PolyObjects.h"
#include "Matrix.h"

class Collectable
{
protected:
	GLuint collectableTextureId;
	double posX, posY, rot;
	double size;
	polygon objectPoly, objectPolyN;

public:
	Collectable();
	polygon getPolygonN();
};

#endif 