#include <gl/gl.h>			

class CollisionCircle
{
private:
	double radius;

public:
	CollisionCircle();
	virtual void isColiding(double posX, double posY, double rot);
};