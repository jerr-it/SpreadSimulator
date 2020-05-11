/**
 * @file
 * Quadtree structure, specifically designed to be used with the SpreadSimulators Entity-Component-System
 *
 * @author cherrysrc
 * @data 11.05.2020
 * @copyright MIT-License
 */

#ifndef SPREADSIMREVIVED_QUADTREE_H
#define SPREADSIMREVIVED_QUADTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Rect.h"
#include "PositionIndexPairList.h"

#define NODE_CAPACITY 4

/**
 * @struct Quadtree
 * @brief The main quadtree struct
 */
typedef struct Quadtree
{
    Rect boundary;

    PositionIndexPair ipPairs[NODE_CAPACITY];
    int ipPairsSize;

    struct Quadtree* northWest;
    struct Quadtree* northEast;
    struct Quadtree* southWest;
    struct Quadtree* southEast;
} Quadtree;

/**
 * Create a new Quadtree object
 * @param boundary Main boundary of the quadtree
 * @return New Quadtree object
 */
Quadtree* createQuadTree(Rect* boundary);

/**
 * Insert a PositionIndexPair into the tree
 * @param tree the tree
 * @param pair the pair
 * @return true if successful, false if position outside boundary
 */
bool insert(Quadtree* tree, PositionIndexPair pair);

/**
 * Divide the tree into 4 same segments
 * @param tree Tree
 */
void subdivide(Quadtree* tree);

/**
 * Get a list of PositionIndexPairs inside a given rectangular area
 * @param tree Tree to query
 * @param range The desired area
 * @return List of PositionIndexPairs that lie within the range
 */
PositionIndexPairList queryRange(Quadtree* tree, Rect* range);

/**
 * Free up used memory
 * @param tree Tree
 */
void freeQuadtree(Quadtree* tree);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_QUADTREE_H
