#ifndef OBJECT_H
#define OBJECT_H



#include <gl/gl.h>			
#include "PolyObjects.h"
#include "Matrix.h"

class Object
{
protected:
	GLuint enemyTextureId;
	double posX, posY, rot;
	double size;
	polygon objectPoly, objectPolyN;

public:
	Object();
	polygon getPolygonN();
};

#endif 