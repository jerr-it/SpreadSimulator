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
    SimulationSettings* settings;
    SimulatorStats* stats;

    Vector2** positions;
    Vector2** velocities;
    Vector2** accelerations;

    MedicalComponent** medComponents;
} SpreadSimulator;

SpreadSimulator* createSimulator(SimulationSettings* settings);

void printStats(SpreadSimulator* simulator);

void tick(SpreadSimulator* simulator);

void tickEvent(SpreadSimulator* stats);

void infectionEvent(SpreadSimulator* stats, int index);

void cureEvent(SpreadSimulator* stats, int index);

void deathEvent(SpreadSimulator* stats, int index);

void hospitalizeEvent(SpreadSimulator* stats, int index);

void dehospitalizeEvent(SpreadSimulator* stats, int index);

void cleanup(SpreadSimulator* simulator);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_SPREADSIMULATOR_H
