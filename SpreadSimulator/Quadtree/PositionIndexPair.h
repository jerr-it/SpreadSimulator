/**
 * @file
 * Struct holding a position and an index
 *
 * @author cherrysrc
 * @data 11.05.2020
 * @copyright MIT-License
 */

#ifndef SPREADSIMREVIVED_POSITIONINDEXPAIR_H
#define SPREADSIMREVIVED_POSITIONINDEXPAIR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Vector2.h"

/**
 * @struct PositionIndexPair
 * @brief Struct holding a position and an index
 */
typedef struct
{
    int index;
    Vector2 position;
} PositionIndexPair;

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_POSITIONINDEXPAIR_H
