/**
 * @file
 * Rect calculations (for Quadtree)
 *
 * @author cherrysrc
 * @data 11.05.2020
 * @copyright MIT-License
 */

#ifndef SPREADSIMREVIVED_RECT_H
#define SPREADSIMREVIVED_RECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Vector2.h"
#include <stdbool.h>

/**
 * @struct Rect
 * @brief Struct modelling a rectangle using center and half dimension
 */
typedef struct
{
    Vector2 center;
    Vector2 halfDim;
} Rect;

/**
 * Create rect from center and half dimension
 * @param center center of rect
 * @param halfdim half dimension
 * @return New Rect object
 */
Rect createRect(Vector2* center, Vector2* halfdim);

/**
 * Check if a rect contains a point
 * @param rect Rect
 * @param point Point
 * @return True if point is within rect
 */
bool containsPoint(Rect* rect, Vector2* point);

/**
 * Checks if two rects intersect
 * @param a Rect
 * @param b Rect
 * @return true if rects intersect
 */
bool intersects(Rect* a, Rect* b);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_RECT_H
