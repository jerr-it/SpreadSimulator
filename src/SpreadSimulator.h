//
// Created by jerrit on 26.03.20.
//

#ifndef SPREADSIM_SPREADSIMULATOR_H
#define SPREADSIM_SPREADSIMULATOR_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Vector;

typedef struct {
    int timeUnitSinceInfection;
    int timeUnitUntilEnd;

    int infectionChance;
    int survivalChance;
    int detectionChance;

    bool isInfected;
    bool isMobile;
    bool isCured;
    bool isDead;

    bool inHospital;
    double influenceRadius;
} Infectable;

typedef struct {
    Vector *position;
    Vector *movement;
    Vector *confinedSpace;
    Infectable *infection;
} Entity;

typedef struct {
    Entity **entities;
    int entityCount;

    int unaffected;
    int infected;
    int cured;
    int dead;

    int hospitalCapacity;
    int hospitalized;

    int testsPerTick;

    int tick;
} SpreadSimulator;

Vector *createVector(double x, double y);

Vector *addVector(Vector a, Vector b);

double distSq(Vector a, Vector b);

Infectable* createInfectable(int tUSinceInfection, int tUUntilEnd,int infChance, int survChance, int detect, bool infected, bool mobil, double infRadius);

Entity *createEntity(Vector *pos, Vector *vel, Vector *conf, Infectable *inf);

SpreadSimulator *
createSpreadSimulator(int samples, int infectedAtStart, int mobileCount, int hospitalCap, int testspT, int tUForHeal,int infectionChance, int survivalChance, int detectChance, double influenceRad, Vector *confinedSpace);

void tick(SpreadSimulator *simulator);

void freeVector(Vector *v);

void freeInfectable(Infectable *inf);

void freeEntity(Entity *ent);

void freeSpreadSimulator(SpreadSimulator *sim);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIM_SPREADSIMULATOR_H
