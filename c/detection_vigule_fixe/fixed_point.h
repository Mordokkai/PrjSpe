#ifndef FIXED_POINT_H_INCLUDED
#define FIXED_POINT_H_INCLUDED

#include<stdbool.h>
#include<inttypes.h>


#define SIZE 16

typedef struct {
    int32_t val;
    int e;
    int v;
}FixedPoint;

bool initFixedPoint(FixedPoint* fx, int e, int v);
bool convertDouble(double x, FixedPoint* fx);
FixedPoint PLUS(FixedPoint x1, FixedPoint x2);
int* fixedPointtoTab(FixedPoint x);
int minE(double x);


#endif // FIXED_POINT_H_INCLUDED
