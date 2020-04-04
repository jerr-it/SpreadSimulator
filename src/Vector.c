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

void addVector(Vector* a, Vector* b){
    a->x += b->x;
    a->y += b->y;
}

void scaleVector(Vector* a, double scale){
    a->x *= scale;
    a->y *= scale;
}

void limitVector(Vector* a, double limit){
    if(getMagnitude(a) > limit){
        normalizeVector(a);
        scaleVector(a, limit);
    }
}

void normalizeVector(Vector* a){
    double mag = getMagnitude(a);
    scaleVector(a, 1/mag);
}

double getMagnitude(Vector* a){
    return sqrt(a->x * a->x + a->y * a->y);
}

double distSq(Vector a, Vector b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}