//
// Created by jerrit on 31.03.20.
//

#ifndef SPREADSIM_VECTOR_H
#define SPREADSIM_VECTOR_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
    double x;
    double y;
} Vector;

Vector *createVector(double x, double y);

Vector *addVector(Vector a, Vector b);

double distSq(Vector a, Vector b);

void freeVector(Vector *v);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIM_VECTOR_H
