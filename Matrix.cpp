
// 4x4 matrix library

#include "Matrix.h"


void printMat(float *m)
{
	for (int i = 0; i<4; ++i)
		fprintf(stdout, "%f %f %f %f\n", m[i], m[i + 4], m[i + 8], m[i + 12]);
	fprintf(stdout, "\n");
}

void setIdentity(float *m)
{
	for (int i = 0; i<16; ++i)
		m[i] = 0.0;
	m[0] = 1.0;
	m[5] = 1.0;
	m[10] = 1.0;
	m[15] = 1.0;
}

void setRotMat(float *m, float angle, int axis)
{
	setIdentity(m);
	switch (axis){
	case 0: // x-axis
		// for 3D only
		break;
	case 1: // y-axis
		// for 3D only
		break;
	case 2: // z-axis
		m[0] = m[5] = cos(angle);
		m[4] = -sin(angle);
		m[1] = -m[4];
		break;
	}
}

void setTraMat(float *m, float x, float y, float z)
{
	setIdentity(m);
	m[12] = x;
	m[13] = y;
	m[14] = z;
}

void MultMat(float *m1, float *m2, float *m)
{
	for (int i = 0; i<4; ++i){
		for (int j = 0; j<4; ++j){
			m[j * 4 + i] = m1[i] * m2[4 * j] + m1[i + 4] * m2[4 * j + 1] + m1[i + 8] * m2[4 * j + 2] + m1[i + 12] * m2[4 * j + 3];
		}
	}
}

void MultMatPostVec(float *m1, float *v1, float *v)
{
	for (int j = 0; j<4; ++j){
		v[j] = m1[j * 4] * v1[0] + m1[j * 4 + 1] * v1[1] + m1[j * 4 + 2] * v1[2] + m1[j * 4 + 3] * v1[3];
	}
}

void MultMatPreVec(float *m1, float *v1, float *v)
{
	for (int j = 0; j<4; ++j){
		v[j] = m1[j] * v1[0] + m1[j + 4] * v1[1] + m1[j + 8] * v1[2] + m1[j + 12] * v1[3];
	}
}

void MultMatPre2DPoint(float *m1, point *v, point *vN)
{
	float v1[4], v2[4];
	v1[0] = v->x; v1[1] = v->y; v1[2] = 0.0; v1[3] = 1.0; //start from default vector!
	for (int j = 0; j<4; ++j){
		v2[j] = m1[j] * v1[0] + m1[j + 4] * v1[1] + m1[j + 8] * v1[2] + m1[j + 12] * v1[3];
	}
	vN->x = v2[0];
	vN->y = v2[1];
}