#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <math.h>

#include "PolyObjects.h"

void printMat(float *);
void setIdentity(float *);
void setRotMat(float *, float, int);
void setTraMat(float *, float, float, float);
void MultMat(float *, float *, float *);
void MultMatPostVec(float *M, float *vo, float *v);
void MultMatPreVec(float *M, float *vo, float *v);
void MultMatPre2DPoint(float *M, point *v, point *vN);

#endif