//
// Created by jerrit on 31.03.20.
//

#ifndef SPREADSIM_VECTOR_H
#define SPREADSIM_VECTOR_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Vector;

Vector *createVector(double x, double y);

void addVector(Vector* a, Vector* b);
void scaleVector(Vector* a, double scale);

void limitVector(Vector* a, double limit);
void normalizeVector(Vector* a);
double getMagnitude(Vector* a);

double distSq(Vector a, Vector b);

void freeVector(Vector *v);

#ifdef __cplusplus
}
#endif


#endif //SPREADSIM_VECTOR_H
