//
// Created by jerrit on 26.03.20.
//
#include "SpreadSimulator.h"

Vector* createVector(double x, double y){
    Vector* vec = (Vector*)calloc(1, sizeof(Vector));

    vec->x = x;
    vec->y = y;

    return vec;
}

Vector* addVector(Vector a, Vector b){
    Vector* added = createVector(0, 0);

    added->x = a.x + b.x;
    added->y = a.y + b.y;

    return added;
}

double distSq(Vector a, Vector b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

Infectable* createInfectable(int tUSinceInfection, int tUUntilEnd,int infChance, int survChance, int detectChance, bool infected, bool mobil, double infRadius){
    Infectable* inf = (Infectable*)calloc(1, sizeof(Infectable));

    inf->timeUnitSinceInfection = tUSinceInfection;
    inf->timeUnitUntilEnd = tUUntilEnd;
    inf->infectionChance = infChance;
    inf->survivalChance = survChance;
    inf->isInfected = infected;
    inf->isMobile = mobil;
    inf->influenceRadius = infRadius;
    inf->isCured = false;
    inf->isDead = false;
    inf->inHospital = false;
    inf->detectionChance = detectChance;

    return inf;
}

Entity* createEntity(Vector* pos, Vector* vel, Vector* conf, Infectable* inf){
    Entity* ent = (Entity*)calloc(1, sizeof(Entity));

    ent->position = pos;
    ent->movement = vel;
    ent->confinedSpace = conf;
    ent->infection = inf;

    return ent;
}

SpreadSimulator* createSpreadSimulator(int samples,int infectedAtStart, int mobileCount, int hospitalcap, int testspT, int tUForHeal,int infectionChance, int survivalChance, int detectChance, double influenceRad, Vector* confinedSpace){
    SpreadSimulator* sim = (SpreadSimulator*)calloc(1, sizeof(SpreadSimulator));

    sim->entityCount = samples;
    sim->entities = (Entity**)calloc(samples, sizeof(Entity*));

    for(int i = 0; i < samples; i++)
    {
        bool infected = false;
        if(i < infectedAtStart){
            infected = true;
        }

        bool mobile = false;
        if(i < mobileCount){
            mobile = true;
        }

        Infectable* inf = createInfectable(0, tUForHeal,infectionChance, survivalChance, detectChance, infected, mobile, influenceRad);
        sim->entities[i] = createEntity(createVector(rand() % (int)confinedSpace->x, rand() % (int)confinedSpace->y), createVector(rand() % 5 - 2.5, rand() % 5 - 2.5), confinedSpace, inf);
    }

    sim->cured = 0;
    sim->infected = infectedAtStart;
    sim->dead = 0;
    sim->unaffected = samples - infectedAtStart;
    sim->hospitalCapacity = hospitalcap;
    sim->hospitalized = 0;
    sim->testsPerTick = testspT;

    sim->tick = 0;

    return sim;
}

void tick(SpreadSimulator* simulator){
    simulator->tick++;

    for(int i = 0; i < simulator->entityCount; i++){
        //Update Entities
        if(simulator->entities[i]->infection->isInfected)
        {
            for(int j = 0; j < simulator->entityCount; j++)
            {
                if(i == j){
                    continue;
                }

                if(simulator->entities[j]->infection->isCured || simulator->entities[j]->infection->isDead || simulator->entities[j]->infection->isInfected){
                    continue;
                }

                if(distSq(*simulator->entities[i]->position, *simulator->entities[j]->position) < simulator->entities[i]->infection->influenceRadius * simulator->entities[i]->infection->influenceRadius)
                {
                    int percent = rand() % 100;
                    if(percent <= simulator->entities[i]->infection->infectionChance){
                        simulator->entities[j]->infection->isInfected = true;
                        simulator->infected++;
                        simulator->unaffected--;
                    }
                }
            }

            simulator->entities[i]->infection->timeUnitSinceInfection++;
            if(simulator->entities[i]->infection->timeUnitSinceInfection >= simulator->entities[i]->infection->timeUnitUntilEnd)
            {
                int percent = rand() % 100;
                if(percent <= simulator->entities[i]->infection->survivalChance)
                {
                    simulator->entities[i]->infection->isInfected = false;
                    simulator->entities[i]->infection->isCured = true;

                    simulator->infected--;
                    simulator->cured++;
                }else{
                    simulator->entities[i]->infection->isInfected = false;
                    simulator->entities[i]->infection->isDead = true;
                    simulator->entities[i]->infection->isMobile = false;

                    simulator->infected--;
                    simulator->dead++;
                }

                if(simulator->entities[i]->infection->inHospital){
                    simulator->hospitalized--;
                    simulator->entities[i]->infection->inHospital = false;
                }
            }
        }

        if(simulator->entities[i]->infection->isMobile){
            Vector* newPos = addVector(*simulator->entities[i]->position, *simulator->entities[i]->movement);
            free(simulator->entities[i]->position);
            simulator->entities[i]->position = newPos;

            if(simulator->entities[i]->position->x <= 0 || simulator->entities[i]->position->x >= simulator->entities[i]->confinedSpace->x){
                simulator->entities[i]->movement->x *= -1;
            }
            if(simulator->entities[i]->position->y <= 0 || simulator->entities[i]->position->y >= simulator->entities[i]->confinedSpace->y){
                simulator->entities[i]->movement->y *= -1;
            }
        }
    }

    for(int i = 0; i < simulator->testsPerTick; i++){
        int randomIndex = rand() % simulator->entityCount;
        if(simulator->entities[randomIndex]->infection->isInfected){
            int percent = rand() % 100;
            if(percent <= simulator->entities[randomIndex]->infection->detectionChance
                && simulator->tick % 20 == 0
                && simulator->hospitalized < simulator->hospitalCapacity
                && !simulator->entities[randomIndex]->infection->inHospital)
            {
                simulator->hospitalized++;
                simulator->entities[randomIndex]->infection->survivalChance = 90;
                simulator->entities[randomIndex]->infection->inHospital = true;
                simulator->entities[randomIndex]->infection->isMobile = false;
            }
        }
    }
}

void freeEntity(Entity* ent){
    free(ent->position);
    free(ent->movement);
    free(ent->confinedSpace);
    free(ent->infection);

    free(ent);
}

void freeSpreadSimulator(SpreadSimulator* sim){
    for(int i = 0; i < sim->entityCount; i++){
        freeEntity(sim->entities[i]);
    }
    free(sim->entities);
    free(sim);
}