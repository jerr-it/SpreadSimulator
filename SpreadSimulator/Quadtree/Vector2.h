#ifndef SPREADSIM_VECTOR2_H
#define SPREADSIM_VECTOR2_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
} Vector2;

Vector2 createVector(double x, double y);

void addVector(Vector2* a, Vector2* b);

void scaleVector(Vector2* a, double scale);

double getMagnitude(Vector2* a);

void limitVector(Vector2* a, double limit);

void normalizeVector(Vector2* a);

double distSq(Vector2* a, Vector2* b);

#ifdef __cplusplus
}
#endif


#endif //SPREADSIM_VECTOR_H
