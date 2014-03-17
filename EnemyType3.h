#include <gl/gl.h>			
#include "Enemy.h"

class EnemyType3 : public Enemy
{

private:
	float enemySize = 2;
	float mb[16], mb1[16], mb2[16];

public:
	EnemyType3();
	virtual void initialise();
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY);
	virtual void render();
};
