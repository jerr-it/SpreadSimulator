#include "Quadtree.h"

Quadtree* createQuadTree(Rect* boundary)
{
    Quadtree* tree = calloc(1, sizeof(Quadtree));

    tree->boundary = *boundary;
    tree->ipPairsSize = 0;

    tree->northWest = NULL;
    tree->northEast = NULL;
    tree->southWest = NULL;
    tree->southEast = NULL;

    return tree;
}

bool insert(Quadtree* tree, PositionIndexPair pair)
{
    if (!containsPoint(&tree->boundary, &pair.position))
        return false;

    if (tree->ipPairsSize < NODE_CAPACITY && tree->northWest == NULL)
    {
        tree->ipPairs[tree->ipPairsSize++] = pair;
        return true;
    }

    if (tree->northWest == NULL)
    {
        subdivide(tree);
    }

    if (insert(tree->northWest, pair))
        return true;
    if (insert(tree->northEast, pair))
        return true;
    if (insert(tree->southWest, pair))
        return true;
    if (insert(tree->southEast, pair))
        return true;

    return false;
}

void subdivide(Quadtree* tree)
{
    Rect tmp_rect;

    // NORTH WEST
    Vector2 northWestPos = createVector(
            tree->boundary.center.x - tree->boundary.halfDim.x / 2,
            tree->boundary.center.y - tree->boundary.halfDim.y / 2);
    Vector2 northWestDim =
            createVector(tree->boundary.halfDim.x / 2, tree->boundary.halfDim.y / 2);

    tmp_rect = createRect(&northWestPos, &northWestDim);
    tree->northWest = createQuadTree(&tmp_rect);

    // NORTH EAST
    Vector2 northEastPos = createVector(
            tree->boundary.center.x + tree->boundary.halfDim.x / 2,
            tree->boundary.center.y - tree->boundary.halfDim.y / 2);
    Vector2 northEastDim =
            createVector(tree->boundary.halfDim.x / 2, tree->boundary.halfDim.y / 2);

    tmp_rect = createRect(&northEastPos, &northEastDim);
    tree->northEast = createQuadTree(&tmp_rect);

    // SOUTH WEST
    Vector2 southWestPos = createVector(
            tree->boundary.center.x - tree->boundary.halfDim.x / 2,
            tree->boundary.center.y + tree->boundary.halfDim.y / 2);
    Vector2 southWestDim =
            createVector(tree->boundary.halfDim.x / 2, tree->boundary.halfDim.y / 2);

    tmp_rect = createRect(&southWestPos, &southWestDim);
    tree->southWest = createQuadTree(&tmp_rect);

    // SOUTH EAST
    Vector2 southEastPos = createVector(
            tree->boundary.center.x + tree->boundary.halfDim.x / 2,
            tree->boundary.center.y + tree->boundary.halfDim.y / 2);
    Vector2 southEastDim =
            createVector(tree->boundary.halfDim.x / 2, tree->boundary.halfDim.y / 2);

    tmp_rect = createRect(&southEastPos, &southEastDim);
    tree->southEast = createQuadTree(&tmp_rect);
}

PositionIndexPairList queryRange(Quadtree* tree, Rect* range)
{
    PositionIndexPairList list = createPositionIndexPairList(4);

    if (!intersects(&tree->boundary, range))
        return list;

    for (int i = 0; i < tree->ipPairsSize; i++)
    {
        if (containsPoint(range, &tree->ipPairs[i].position))
        {
            list = pushPositionIndexPair(list, tree->ipPairs[i]);
        }
    }

    if (tree->northWest == NULL)
        return list;

    list = appendPositionIndexPairList(list, queryRange(tree->northWest, range));
    list = appendPositionIndexPairList(list, queryRange(tree->northEast, range));
    list = appendPositionIndexPairList(list, queryRange(tree->southWest, range));
    list = appendPositionIndexPairList(list, queryRange(tree->southEast, range));

    return list;
}

void freeQuadtree(Quadtree* tree)
{
    if (!tree)
        return;
    freeQuadtree(tree->northWest);
    freeQuadtree(tree->northEast);
    freeQuadtree(tree->southWest);
    freeQuadtree(tree->southEast);

    free(tree);
}
