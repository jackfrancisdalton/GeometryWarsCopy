#ifndef OBJECT_H
#define OBJECT_H



#include <gl/gl.h>			
#include "PolyObjects.h"
#include "Matrix.h"

class Object
{
protected:
	GLuint objectTextureId;
	double posX, posY, rot;
	double size;
	polygon objectPoly, objectPolyN;

public:
	Object();
	polygon getPolygonN();
	virtual void update(double deltaT, double prevDeltaT) = 0;
	virtual void render() = 0;
};

#endif 