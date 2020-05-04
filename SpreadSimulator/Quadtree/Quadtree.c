#include "Quadtree.h"

Quadtree* createQuadTree(Rect* boundary)
{
    Quadtree* tree = (Quadtree*) calloc(NODE_CAPACITY, sizeof(Quadtree));

    tree->boundary = boundary;
    tree->ipPairs = (PositionIndexPair*) calloc(NODE_CAPACITY, sizeof(PositionIndexPair));
    tree->ipPairsSize = 0;

    tree->northWest = NULL;
    tree->northEast = NULL;
    tree->southWest = NULL;
    tree->southEast = NULL;

    return tree;
}

bool insert(Quadtree* tree, PositionIndexPair pair)
{
    if (!containsPoint(tree->boundary, &pair.position)) return false;

    if (tree->ipPairsSize < NODE_CAPACITY && tree->northWest == NULL)
    {
        tree->ipPairs[tree->ipPairsSize++] = pair;
        return true;
    }

    if (tree->northWest == NULL)
    {
        subdivide(tree);
    }

    if (insert(tree->northWest, pair)) return true;
    if (insert(tree->northEast, pair)) return true;
    if (insert(tree->southWest, pair)) return true;
    if (insert(tree->southEast, pair)) return true;

    return false;
}

void subdivide(Quadtree* tree)
{
    //NORTH WEST
    Vector2* northWestPos = createVector(
            tree->boundary->center->x - tree->boundary->halfDim->x / 2,
            tree->boundary->center->y - tree->boundary->halfDim->y / 2
    );
    Vector2* northWestDim = createVector(
            tree->boundary->halfDim->x / 2,
            tree->boundary->halfDim->y / 2
    );

    tree->northWest = createQuadTree(createRect(northWestPos, northWestDim));

    //NORTH EAST
    Vector2* northEastPos = createVector(
            tree->boundary->center->x + tree->boundary->halfDim->x / 2,
            tree->boundary->center->y - tree->boundary->halfDim->y / 2
    );
    Vector2* northEastDim = createVector(
            tree->boundary->halfDim->x / 2,
            tree->boundary->halfDim->y / 2
    );

    tree->northEast = createQuadTree(createRect(northEastPos, northEastDim));

    //SOUTH WEST
    Vector2* southWestPos = createVector(
            tree->boundary->center->x - tree->boundary->halfDim->x / 2,
            tree->boundary->center->y + tree->boundary->halfDim->y / 2
    );
    Vector2* southWestDim = createVector(
            tree->boundary->halfDim->x / 2,
            tree->boundary->halfDim->y / 2
    );

    tree->southWest = createQuadTree(createRect(southWestPos, southWestDim));

    //SOUTH EAST
    Vector2* southEastPos = createVector(
            tree->boundary->center->x + tree->boundary->halfDim->x / 2,
            tree->boundary->center->y + tree->boundary->halfDim->y / 2
    );
    Vector2* southEastDim = createVector(
            tree->boundary->halfDim->x / 2,
            tree->boundary->halfDim->y / 2
    );

    tree->southEast = createQuadTree(createRect(southEastPos, southEastDim));
}

PositionIndexPairList queryRange(Quadtree* tree, Rect* range)
{
    PositionIndexPairList list = createPositionIndexPairList(4);

    if (!intersects(tree->boundary, range)) return list;

    for (int i = 0; i < tree->ipPairsSize; i++)
    {
        if (containsPoint(range, &tree->ipPairs[i].position))
        {
            list = pushPositionIndexPair(list, tree->ipPairs[i]);
        }
    }

    if (tree->northWest == NULL) return list;

    list = appendPositionIndexPairList(list, queryRange(tree->northWest, range));
    list = appendPositionIndexPairList(list, queryRange(tree->northEast, range));
    list = appendPositionIndexPairList(list, queryRange(tree->southWest, range));
    list = appendPositionIndexPairList(list, queryRange(tree->southEast, range));

    return list;
}

void freeQuadtree(Quadtree* tree)
{
    if (tree->northWest) freeQuadtree(tree->northWest);
    if (tree->northEast) freeQuadtree(tree->northEast);
    if (tree->southWest) freeQuadtree(tree->southWest);
    if (tree->southEast) freeQuadtree(tree->southEast);

    freeRect(tree->boundary);

    free(tree->ipPairs);
    free(tree);
}