#include <gl/gl.h>			
#include "Enemy.h"

class EnemyType1 : public Enemy
{

public:
	EnemyType1();
	virtual void initialise();											
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY);
	virtual void render();												
};
