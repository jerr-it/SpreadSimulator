#ifndef SPREADSIM_SPREADSIMULATIONSETTINGS_H
#define SPREADSIM_SPREADSIMULATIONSETTINGS_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>

typedef struct
{
    int entityCount;
    int initialInfected;
    int mobileEntities;
    int hospitalCapacity;
    int testsPerTick;
    int ticksUntilHealed;
    int chanceOfInfectionUponContact;
    int chanceOfSurviving;
    int chanceOfDetection;
    int influenceRadius;
    int confinedSpaceX;
    int confinedSpaceY;
} SpreadSimulationSettings;

SpreadSimulationSettings* createSimSettings(int entCount, int initialInfected, int mobileEntities, int hospitalCap, int testspertick, int ticksUH, int infChance, int survChance, int detectChance, int infRadius, int limX, int limY);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIM_SPREADSIMULATIONSETTINGS_H
