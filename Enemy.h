#include <gl/gl.h>			

class Enemy
{
protected:
	GLuint enemyTextureId;
	int health;
	double posX, posY, rot;
	int state;
	int id;
	float textureX, textureY;
	int refreshWait, refreshIndex;
	int frameCounter;

public:
	Enemy();
	virtual double getEnemyRot();
	virtual double getEnemyX();
	virtual double getEnemyY();
	virtual void initialise();											// Called on application start up
	virtual void shutdown();											// Called on application shut down
	virtual void onSwitchIn();											// Activity switch in; called when the activity changes and this one switches in
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY);
	virtual void render();												// Render function
};
