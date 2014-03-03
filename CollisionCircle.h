#include <gl/gl.h>			

class CollisionCircle
{
private:
	double radius, centreX, centreY;

public:
	CollisionCircle();
	CollisionCircle(double posX, double posY);
	virtual void Update(double posX, double posY);
	virtual bool isColidingWith(CollisionCircle &other);
	virtual double getX();
	virtual double getY();
};