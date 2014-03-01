#include <gl/gl.h>			
#include "Enemy.h"

class EnemyType3 : public Enemy
{

public:
	EnemyType3();
	virtual void initialise();
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY);
	virtual void render();
};
