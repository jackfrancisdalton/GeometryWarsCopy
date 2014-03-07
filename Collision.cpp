
/***********************************/
/* Separating Axis Test in 2D      */
/* Written by R.J. Lapeer, 02/2013 */
/***********************************/

#include "Collision.h"

int SAT2D(polygon *p1, polygon *p2) // Note that this function can be made much smaller if the 2 polygons are combined in an array of 2
{
	float axis[2], len, proj[4];
	// 2 tests for each edge of a polygon = 4 tests = 4 axes

	// Axis 1 Poly 1
	axis[0] = p1->vert[1].x - p1->vert[0].x;
	axis[1] = p1->vert[1].y - p1->vert[0].y;
	len = sqrt(axis[0] * axis[0] + axis[1] * axis[1]);
	axis[0] /= len; axis[1] /= len;  // unit vector
	// project second poly points on axis
	proj[0] = (p2->vert[0].x - p1->vert[0].x)*axis[0] + (p2->vert[0].y - p1->vert[0].y)*axis[1];   // dot product
	proj[1] = (p2->vert[1].x - p1->vert[0].x)*axis[0] + (p2->vert[1].y - p1->vert[0].y)*axis[1];
	proj[2] = (p2->vert[2].x - p1->vert[0].x)*axis[0] + (p2->vert[2].y - p1->vert[0].y)*axis[1];
	proj[3] = (p2->vert[3].x - p1->vert[0].x)*axis[0] + (p2->vert[3].y - p1->vert[0].y)*axis[1];
	//fprintf(stdout,"1 - %f %f, %f %f %f %f, %f\n",axis[0],axis[1],proj[0],proj[1],proj[2],proj[3],len);
	if (SATest(proj, len)) return 1;

	// Axis 2 Poly 1
	axis[0] = p1->vert[2].x - p1->vert[1].x;
	axis[1] = p1->vert[2].y - p1->vert[1].y;
	len = sqrt(axis[0] * axis[0] + axis[1] * axis[1]);
	axis[0] /= len; axis[1] /= len;  // unit vector
	// project second poly points on axis
	proj[0] = (p2->vert[0].x - p1->vert[1].x)*axis[0] + (p2->vert[0].y - p1->vert[1].y)*axis[1];   // dot product
	proj[1] = (p2->vert[1].x - p1->vert[1].x)*axis[0] + (p2->vert[1].y - p1->vert[1].y)*axis[1];
	proj[2] = (p2->vert[2].x - p1->vert[1].x)*axis[0] + (p2->vert[2].y - p1->vert[1].y)*axis[1];
	proj[3] = (p2->vert[3].x - p1->vert[1].x)*axis[0] + (p2->vert[3].y - p1->vert[1].y)*axis[1];
	//fprintf(stdout,"2 - %f %f, %f %f %f %f, %f\n",axis[0],axis[1],proj[0],proj[1],proj[2],proj[3],len);
	if (SATest(proj, len)) return 1;

	// Axis 3 Poly 2
	axis[0] = p2->vert[1].x - p2->vert[0].x;
	axis[1] = p2->vert[1].y - p2->vert[0].y;
	len = sqrt(axis[0] * axis[0] + axis[1] * axis[1]);
	axis[0] /= len; axis[1] /= len;  // unit vector
	// project second poly points on axis
	proj[0] = (p1->vert[0].x - p2->vert[0].x)*axis[0] + (p1->vert[0].y - p2->vert[0].y)*axis[1];   // dot product
	proj[1] = (p1->vert[1].x - p2->vert[0].x)*axis[0] + (p1->vert[1].y - p2->vert[0].y)*axis[1];
	proj[2] = (p1->vert[2].x - p2->vert[0].x)*axis[0] + (p1->vert[2].y - p2->vert[0].y)*axis[1];
	proj[3] = (p1->vert[3].x - p2->vert[0].x)*axis[0] + (p1->vert[3].y - p2->vert[0].y)*axis[1];
	//fprintf(stdout,"3 - %f %f, %f %f %f %f, %f\n",axis[0],axis[1],proj[0],proj[1],proj[2],proj[3],len);
	if (SATest(proj, len)) return 1;

	// Axis 4 Poly 2
	axis[0] = p2->vert[2].x - p2->vert[1].x;
	axis[1] = p2->vert[2].y - p2->vert[1].y;
	len = sqrt(axis[0] * axis[0] + axis[1] * axis[1]);
	axis[0] /= len; axis[1] /= len;  // unit vector
	// project second poly points on axis
	proj[0] = (p1->vert[0].x - p2->vert[1].x)*axis[0] + (p1->vert[0].y - p2->vert[1].y)*axis[1];   // dot product
	proj[1] = (p1->vert[1].x - p2->vert[1].x)*axis[0] + (p1->vert[1].y - p2->vert[1].y)*axis[1];
	proj[2] = (p1->vert[2].x - p2->vert[1].x)*axis[0] + (p1->vert[2].y - p2->vert[1].y)*axis[1];
	proj[3] = (p1->vert[3].x - p2->vert[1].x)*axis[0] + (p1->vert[3].y - p2->vert[1].y)*axis[1];
	//fprintf(stdout,"4 - %f %f, %f %f %f %f, %f\n",axis[0],axis[1],proj[0],proj[1],proj[2],proj[3],len);
	if (SATest(proj, len)) return 1;

	fprintf(stdout, "No separating axis found!\n");
	return 0;
}

int SATest(float *proj, float len)
{
	float min = proj[0], max = proj[0];
	for (int i = 1; i <= 3; ++i){  // Find minimum and maximum projections - the other two will lie in between and are of no consequence
		if (proj[i]<min)min = proj[i];
		else if (proj[i]>max)max = proj[i];
	}
	//fprintf(stdout, "min = %f, max = %f\n", min, max);
	// comparison noting that the first point of first poly is at distance 0 and the second point at distance len
	// along the edge of the first poly acting as the axis
	if (min > len || max < 0.0) return 1; // found separating axis
	else return 0;
}