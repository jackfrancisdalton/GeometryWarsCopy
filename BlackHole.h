#include <gl/gl.h>			
#include "Object.h"

class BlackHole : public Object
{
private:
	float mb[16], mb1[16], mb2[16];

public:
	BlackHole();
	virtual void initialise();
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY);
	virtual void render();
};
