#include "SimulationSettings.h"

SimulationSettings
createSettings(int EntityCount, int InitialInfected, int InitialMobile, int HospitalCapacity, int TestsPerTick,
               int TicksUntilExpiration, int InfectionChance, int SurvivalChance, int DetectionChance,
               double InfluenceRadius, bool ActiveDistancing, int CentralLocationsCount, int DimX, int DimY)
{
    SimulationSettings settings;

    settings.entityCount = EntityCount;
    settings.initialInfected = InitialInfected;
    settings.mobileCount = InitialMobile;

    settings.hospitalCapacity = HospitalCapacity;
    settings.testsPerTick = TestsPerTick;
    settings.ticksUntilExpiration = TicksUntilExpiration;

    settings.infectionChance = InfectionChance;
    settings.survivalChance = SurvivalChance;
    settings.detectionChance = DetectionChance;

    settings.influenceRadius = InfluenceRadius;
    settings.activeDistancing = ActiveDistancing;

    settings.centralLocationsCount = CentralLocationsCount;

    settings.dimX = DimX;
    settings.dimY = DimY;

    return settings;
}

void saveSettings(SimulationSettings* settings, char* filename)
{
    FILE* fp;

    fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        fprintf(stderr, "Unable to write to file.");
        return;
    }

    fwrite(settings, sizeof(SimulationSettings), 1, fp);

    fclose(fp);
}

void exportSettings(SimulationSettings* settings, char* filename)
{
    FILE* fp;

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "Unable to write to file.");
        return;
    }

    fprintf(fp, "Entitiy count: %i\n", settings->entityCount);
    fprintf(fp, "Initial infected: %i\n", settings->initialInfected);
    fprintf(fp, "Mobile count: %i\n", settings->mobileCount);

    fprintf(fp, "Hospital capacity: %i\n", settings->hospitalCapacity);
    fprintf(fp, "Tests per tick: %i\n", settings->testsPerTick);
    fprintf(fp, "Ticks until expiration: %i\n", settings->ticksUntilExpiration);

    fprintf(fp, "Infection chance: %i\n", settings->infectionChance);
    fprintf(fp, "Survival chance: %i\n", settings->survivalChance);
    fprintf(fp, "Detection chance: %i\n", settings->detectionChance);

    fprintf(fp, "Influence radius: %i\n", settings->influenceRadius);
    fprintf(fp, "Active distancing: %i\n", settings->activeDistancing);

    fprintf(fp, "Central locations count: %i\n", settings->centralLocationsCount);

    fprintf(fp, "X dimension: %i\n", settings->dimX);
    fprintf(fp, "Y dimension: %i\n", settings->dimY);

    fclose(fp);
}

SimulationSettings* loadSettings(char* filename)
{
    FILE* fp;

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        fprintf(stderr, "Unable to read file.");
        return NULL;
    }

    SimulationSettings* settings = (SimulationSettings*) calloc(1, sizeof(SimulationSettings));

    fread(settings, sizeof(SimulationSettings), 1, fp);

    return settings;
}
