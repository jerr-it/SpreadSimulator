#ifndef SPREADSIMREVIVED_RECT_H
#define SPREADSIMREVIVED_RECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Vector2.h"
#include <stdbool.h>

typedef struct
{
    Vector2 center;
    Vector2 halfDim;
} Rect;

Rect createRect(Vector2* center, Vector2* halfdim);

bool containsPoint(Rect* rect, Vector2* point);

bool intersects(Rect* a, Rect* b);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_RECT_H
