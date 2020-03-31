#include "SpreadSimulationSettings.h"

SpreadSimulationSettings* createSimSettings(int entCount, int initialInfected, int mobileEntities, int hospitalCap, int testspertick, int ticksUH, int infChance, int survChance, int detectChance, int infRadius, int limX, int limY){
    if(mobileEntities > entCount || initialInfected > entCount){
        return NULL;
    }

    if(infChance < 0 || infChance > 100 || survChance < 0 || survChance > 100 || detectChance < 0 || detectChance > 100){
        return NULL;
    }

    SpreadSimulationSettings* settings = (SpreadSimulationSettings*)calloc(1, sizeof(SpreadSimulationSettings));

    settings->entityCount = entCount;
    settings->initialInfected = initialInfected;
    settings->mobileEntities = mobileEntities;
    settings->testsPerTick = testspertick;
    settings->ticksUntilHealed = ticksUH;
    settings->chanceOfInfectionUponContact = infChance;
    settings->chanceOfSurviving = survChance;
    settings->hospitalCapacity = hospitalCap;
    settings->chanceOfDetection = detectChance;
    settings->influenceRadius = infRadius;
    settings->confinedSpaceX = limX;
    settings->confinedSpaceY = limY;

    return settings;
}