#include <gl/gl.h>			
#include "Enemy.h"

class EnemyType2 : public Enemy
{
private: 

public:
	EnemyType2();
	virtual void initialise();
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY);
	virtual void render();
};
