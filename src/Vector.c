//
// Created by jerrit on 31.03.20.
//

#include "Vector.h"

Vector* createVector(double x, double y){
    Vector* vec = (Vector*)calloc(1, sizeof(Vector));

    vec->x = x;
    vec->y = y;

    return vec;
}

Vector* addVector(Vector a, Vector b){
    Vector* added = createVector(0, 0);

    added->x = a.x + b.x;
    added->y = a.y + b.y;

    return added;
}

double distSq(Vector a, Vector b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}