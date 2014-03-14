#include <gl/gl.h>			
#include "Collectable.h"

class ShieldPickUp : public Collectable
{
private:
	float mb[16], mb1[16], mb2[16];

public:
	ShieldPickUp();
	virtual void initialise();
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY);
	virtual void render();
};
