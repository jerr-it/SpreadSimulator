#ifndef SPREADSIMREVIVED_SPREADSIMULATOR_H
#define SPREADSIMREVIVED_SPREADSIMULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Quadtree/Quadtree.h"
#include "MedicalComponent.h"
#include "SimulationSettings.h"
#include "SimulatorStats.h"

#include <time.h>
#include <stdio.h>

typedef struct
{
    SimulationSettings settings;
    SimulatorStats stats;

    Vector2* positions;
    Vector2* velocities;
    Vector2* accelerations;

    MedicalComponent* medComponents;
} SpreadSimulator;

SpreadSimulator createSimulator(SimulationSettings* settings);

void printStats(SpreadSimulator* simulator);

void printStatsRaw(SpreadSimulator* simulator);

void tick(SpreadSimulator* simulator);

void tickEvent(SpreadSimulator* simulator);

void infectionEvent(SpreadSimulator* simulator, int index);

void cureEvent(SpreadSimulator* simulator, int index);

void deathEvent(SpreadSimulator* simulator, int index);

void hospitalizeEvent(SpreadSimulator* simulator, int index);

void dehospitalizeEvent(SpreadSimulator* simulator, int index);

void cleanup(SpreadSimulator* simulator);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_SPREADSIMULATOR_H
