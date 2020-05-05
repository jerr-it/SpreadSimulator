#ifndef SPREADSIMREVIVED_QUADTREE_H
#define SPREADSIMREVIVED_QUADTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Rect.h"
#include "PositionIndexPairList.h"

#define NODE_CAPACITY 4

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

Quadtree* createQuadTree(Rect* boundary);

bool insert(Quadtree* tree, PositionIndexPair pair);

void subdivide(Quadtree* tree);

PositionIndexPairList queryRange(Quadtree* tree, Rect* range);

void freeQuadtree(Quadtree* tree);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_QUADTREE_H
