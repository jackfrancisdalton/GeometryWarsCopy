
// Polygon objects implementation

#include <math.h>
#include "PolyObjects.h"


polygon::polygon(int n)
{
	num_vertices = n;
	vert = new point[num_vertices];
	vertO = new point[num_vertices];
}

polygon::polygon(){}


