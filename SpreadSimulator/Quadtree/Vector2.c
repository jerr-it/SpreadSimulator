#include "Vector2.h"

Vector2 createVector(double x, double y)
{
    Vector2 vec;

    vec.x = x;
    vec.y = y;

    return vec;
}

void addVector(Vector2* a, Vector2* b)
{
    a->x += b->x;
    a->y += b->y;
}

void scaleVector(Vector2* a, double scale)
{
    a->x *= scale;
    a->y *= scale;
}

void limitVector(Vector2* a, double limit)
{
    if (getMagnitude(a) > limit)
    {
        normalizeVector(a);
        scaleVector(a, limit);
    }
}

void normalizeVector(Vector2* a)
{
    double mag = getMagnitude(a);
    scaleVector(a, 1 / mag);
}

double getMagnitude(Vector2* a)
{
    return sqrt(a->x * a->x + a->y * a->y);
}

double distSq(Vector2* a, Vector2* b)
{
    return (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y);
}
