#include <gl/gl.h>			
#include "Object.h"

class JumpPad : public Object
{
private:
	float mb[16], mb1[16], mb2[16];

public:
	JumpPad();
	virtual void initialise();
	virtual void update(double deltaT, double prevDeltaT);
	virtual void render();
};
