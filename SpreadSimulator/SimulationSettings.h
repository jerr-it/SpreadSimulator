#ifndef SPREADSIMREVIVED_SIMULATIONSETTINGS_H
#define SPREADSIMREVIVED_SIMULATIONSETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int entityCount;
    int initialInfected;
    int mobileCount;

    int hospitalCapacity;
    int testsPerTick;
    int ticksUntilExpiration;

    int infectionChance;
    int survivalChance;
    int detectionChance;

    int influenceRadius;
    bool activeDistancing;

    int centralLocationsCount;

    int dimX;
    int dimY;
} SimulationSettings;

SimulationSettings
createSettings(int EntityCount, int InitialInfected, int InitialMobile, int HospitalCapacity, int TestsPerTick,
               int TicksUntilExpiration, int InfectionChance, int SurvivalChance, int DetectionChance,
               double InfluenceRadius, bool ActiveDistancing, int centralLocationsCount, int DimX, int DimY);

void saveSettings(SimulationSettings* settings, char* filename);

void exportSettings(SimulationSettings* settings, char* filename);

SimulationSettings* loadSettings(char* filename);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_SIMULATIONSETTINGS_H
