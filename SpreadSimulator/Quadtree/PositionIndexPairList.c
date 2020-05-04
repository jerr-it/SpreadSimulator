#include "PositionIndexPairList.h"

PositionIndexPairList createPositionIndexPairList(int initialCapacity)
{
    PositionIndexPair* data = (PositionIndexPair*) calloc(initialCapacity, sizeof(PositionIndexPair));

    PositionIndexPairList list = (PositionIndexPairList) {initialCapacity, 0, data};

    return list;
}

PositionIndexPairList pushPositionIndexPair(PositionIndexPairList list, PositionIndexPair pair)
{
    if (list.count >= list.capacity)
    {
        list.capacity *= 2;

        list.data = (PositionIndexPair*) realloc(list.data, list.capacity * sizeof(PositionIndexPair));
    }

    list.data[list.count++] = pair;

    return list;
}

//TODO: innefficent appending
PositionIndexPairList appendPositionIndexPairList(PositionIndexPairList list, PositionIndexPairList appendix)
{
    for (int i = 0; i < appendix.count; i++)
    {
        list = pushPositionIndexPair(list, appendix.data[i]);
    }

    freeList(appendix);
    return list;
}

void freeList(PositionIndexPairList list)
{
    free(list.data);
}