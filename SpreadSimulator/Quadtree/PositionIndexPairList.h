/**
 * @file
 * List of PositionIndexPairs
 *
 * @author cherrysrc
 * @data 11.05.2020
 * @copyright MIT-License
 */

#ifndef SPREADSIMREVIVED_POSITIONINDEXPAIRLIST_H
#define SPREADSIMREVIVED_POSITIONINDEXPAIRLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "PositionIndexPair.h"

/**
 * @struct PositionIndexPairList
 * @brief Dynamic array of PositionIndexPairs
 */
typedef struct
{
    int capacity;
    int count;
    PositionIndexPair* data;
} PositionIndexPairList;

/**
 * Create a new List
 * @param initialCapacity initial reserved space for the list
 * @return the new list
 */
PositionIndexPairList createPositionIndexPairList(int initialCapacity);

/**
 * Add a PositionIndexPair to a given list
 * @param list the list to append to
 * @param pair the pair desired to be appended
 * @return the list including the new element
 */
PositionIndexPairList pushPositionIndexPair(PositionIndexPairList list, PositionIndexPair pair);

/**
 * Append appendix to list
 * @param list list
 * @param appendix list to be appended
 * @return the combined list
 */
PositionIndexPairList appendPositionIndexPairList(PositionIndexPairList list, PositionIndexPairList appendix);

/**
 * Free used memory
 * @param list list to free
 */
void freeList(PositionIndexPairList list);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_POSITIONINDEXPAIRLIST_H
