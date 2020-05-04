#include "Rect.h"

Rect* createRect(Vector2* center, Vector2* halfdim)
{
    Rect* r = (Rect*) calloc(1, sizeof(Rect));

    r->center = center;
    r->halfDim = halfdim;

    return r;
}

bool containsPoint(Rect* rect, Vector2* point)
{
    return (
            point->x > rect->center->x - rect->halfDim->x &&
            point->x < rect->center->x + rect->halfDim->x &&
            point->y > rect->center->y - rect->halfDim->y &&
            point->y < rect->center->y + rect->halfDim->y
    );
}

bool intersects(Rect* a, Rect* b)
{
    return !(
            b->center->x - b->halfDim->x > a->center->x + a->halfDim->x ||
            b->center->x + b->halfDim->x < a->center->x - a->halfDim->x ||
            b->center->y - b->halfDim->y > a->center->y + a->halfDim->y ||
            b->center->y + b->halfDim->y < a->center->y - a->halfDim->y
    );
}

void freeRect(Rect* r)
{
    free(r->halfDim);
    free(r->center);
    free(r);
}