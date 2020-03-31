//
// Created by jerrit on 31.03.20.
//

#include "Entity.h"

Entity* createEntity(Vector* pos, Vector* vel, Vector* conf, Infectable* inf){
    Entity* ent = (Entity*)calloc(1, sizeof(Entity));

    ent->position = pos;
    ent->movement = vel;
    ent->confinedSpace = conf;
    ent->infection = inf;

    return ent;
}

void freeEntity(Entity* ent){
    free(ent->position);
    free(ent->movement);
    free(ent->confinedSpace);
    free(ent->infection);

    free(ent);
}