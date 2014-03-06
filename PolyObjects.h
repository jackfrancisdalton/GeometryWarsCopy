
#ifndef POLYOBJECTS_H
#define POLYOBJECTS_H

// Polygon objects

class point
{
public:
	float x;
	float y;
	//float z;
};

class bsphere
{
public:
	float radius;
	point centre;
};


class polygon
{
public:
	polygon();
	polygon(int);
	int num_vertices;
	point *vert;
	point *vertO;
	bsphere psphere;
};

#endif