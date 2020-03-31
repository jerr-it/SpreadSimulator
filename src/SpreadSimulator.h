#ifndef SPREADSIM_SPREADSIMULATOR_H
#define SPREADSIM_SPREADSIMULATOR_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "SpreadSimulationSettings.h"
#include "Entity.h"

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

SpreadSimulator *
createSpreadSimulator(SpreadSimulationSettings* settings);

void tick(SpreadSimulator *simulator);

void freeSpreadSimulator(SpreadSimulator *sim);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIM_SPREADSIMULATOR_H
