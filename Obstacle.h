#include <gl/gl.h>			

class Obstacle
{
protected:
	GLuint TextureId;
	double posX, posY, rot;
	int state;
	double HitRadius;
	float textureX, textureY;
	int refreshWait, refreshIndex;
	int frameCounter;

public:
	Obstacle();
	virtual void initialise() = 0;											// Called on application start up
	virtual void shutdown();											// Called on application shut down
	virtual void onSwitchIn();											// Activity switch in; called when the activity changes and this one switches in
	virtual void update(double deltaT, double prevDeltaT, double playerX, double playerY) = 0;
	virtual void render() = 0;												// Render function
};