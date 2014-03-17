#include <gl/gl.h>			
#include "Collectable.h"

class ScoreOrb : public Collectable
{
private:
	float mb[16], mb1[16], mb2[16];

public:
	ScoreOrb();
	virtual void initialise();
	virtual void update(double deltaT, double prevDeltaT);
	virtual void render();
};
