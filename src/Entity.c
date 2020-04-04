//
// Created by jerrit on 31.03.20.
//

#include "Entity.h"

Entity* createEntity(Vector* pos, Vector* vel, Vector* conf, Infectable* inf){
    Entity* ent = (Entity*)calloc(1, sizeof(Entity));

    ent->position = pos;
    ent->movement = vel;
    ent->acceleration = createVector(0,0);
    ent->confinedSpace = conf;
    ent->infection = inf;

    return ent;
}

void updateEntityPosition(Entity* entity){
    addVector(entity->position, entity->movement);
    addVector(entity->movement, entity->acceleration);
    entity->acceleration->x = 0;
    entity->acceleration->y = 0;
}

void freeEntity(Entity* ent){
    free(ent->position);
    free(ent->movement);
    free(ent->acceleration);
    free(ent->confinedSpace);
    free(ent->infection);

    free(ent);
}