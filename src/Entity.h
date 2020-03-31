//
// Created by jerrit on 31.03.20.
//

#ifndef SPREADSIM_ENTITY_H
#define SPREADSIM_ENTITY_H

#ifdef __cplusplus
extern "C"{
#endif

#include "Vector.h"
#include "Infectable.h"
#include <stdlib.h>

typedef struct {
    Vector *position;
    Vector *movement;
    Vector *confinedSpace;
    Infectable *infection;
} Entity;

Entity *createEntity(Vector *pos, Vector *vel, Vector *conf, Infectable *inf);

void freeEntity(Entity *ent);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIM_ENTITY_H
