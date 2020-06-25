set(SOURCES
        Vector2.c
        Rect.c
        Quadtree.c
        PositionIndexPairList.c)

set(HEADERS
        Vector2.h
        Rect.h
        Quadtree.h
        PositionIndexPair.h
        PositionIndexPairList.h
        )

add_library(Quadtree SHARED ${SOURCES} ${HEADERS})