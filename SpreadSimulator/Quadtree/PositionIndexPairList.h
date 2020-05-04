#ifndef SPREADSIMREVIVED_POSITIONINDEXPAIRLIST_H
#define SPREADSIMREVIVED_POSITIONINDEXPAIRLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "PositionIndexPair.h"

typedef struct
{
    int capacity;
    int count;
    PositionIndexPair* data;
} PositionIndexPairList;

PositionIndexPairList createPositionIndexPairList(int initialCapacity);

PositionIndexPairList pushPositionIndexPair(PositionIndexPairList list, PositionIndexPair pair);

PositionIndexPairList appendPositionIndexPairList(PositionIndexPairList list, PositionIndexPairList appendix);

void freeList(PositionIndexPairList list);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_POSITIONINDEXPAIRLIST_H
