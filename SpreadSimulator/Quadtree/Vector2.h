/**
 * @file
 * Vector maths file
 *
 * @author cherrysrc
 * @data 11.05.2020
 * @copyright MIT-License
 */

#ifndef SPREADSIM_VECTOR2_H
#define SPREADSIM_VECTOR2_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>
#include <math.h>

/**
 * @struct Vector2
 * @brief Struct modelling a mathematical 2D vector
 */
typedef struct
{
    double x;
    double y;
} Vector2;

/**
 * Create a vector from a given x and y
 * @param x X-Component
 * @param y Y-Component
 * @return New Vector2 object
 */
Vector2 createVector(double x, double y);

/**
 * Adds b to a, b remains unchainged
 * @param a Vector a
 * @param b Vector b
 */
void addVector(Vector2* a, Vector2* b);

/**
 * Multiplies both components of a with scalar
 * @param a vector to scale
 * @param scale scalar
 */
void scaleVector(Vector2* a, double scale);

/**
 * Calculates the length/magnitude of a vector
 * @param a Vector
 * @return length of vector
 */
double getMagnitude(Vector2* a);

/**
 * Limits a vectors length/magnitude to some value
 * @param a Vector
 * @param limit length limit
 */
void limitVector(Vector2* a, double limit);

/**
 * Normalizes a vector
 * @param a Vector
 */
void normalizeVector(Vector2* a);

#ifdef __cplusplus
}
#endif


#endif //SPREADSIM_VECTOR_H
