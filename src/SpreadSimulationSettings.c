#include "SpreadSimulationSettings.h"

SpreadSimulationSettings* createSimSettings(int entCount, int initialInfected, int mobileEntities, int hospitalCap, int testspertick, int ticksUH, int infChance, int survChance, int detectChance, int infRadius, bool activeDist, int limX, int limY){
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
    settings->activeDistancing = activeDist;
    settings->confinedSpaceX = limX;
    settings->confinedSpaceY = limY;

    return settings;
}

void saveSettings(SpreadSimulationSettings* settings, char* filename)
{
    FILE* fp = fopen(filename, "w");

    if(fp == NULL){
        printf("Could not create file.");
        return;
    }

    fprintf(fp, "%i\n", settings->entityCount);
    fprintf(fp, "%i\n", settings->initialInfected);
    fprintf(fp, "%i\n", settings->mobileEntities);
    fprintf(fp, "%i\n", settings->hospitalCapacity);

    fprintf(fp, "%i\n", settings->testsPerTick);
    fprintf(fp, "%i\n", settings->ticksUntilHealed);
    fprintf(fp, "%i\n", settings->chanceOfInfectionUponContact);
    fprintf(fp, "%i\n", settings->chanceOfSurviving);

    fprintf(fp, "%i\n", settings->chanceOfDetection);
    fprintf(fp, "%i\n", settings->influenceRadius);
    fprintf(fp, "%i\n", settings->activeDistancing);
    fprintf(fp, "%i\n", settings->confinedSpaceX);
    fprintf(fp, "%i\n", settings->confinedSpaceY);

    fclose(fp);
}

SpreadSimulationSettings* loadSettings(char* filename)
{
    FILE* fp = fopen(filename, "r");

    if(fp == NULL){
        printf("Could not open file.");
        return NULL;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    int array[12];
    int index = 0;
    while((read = getline(&line, &len, fp)) != -1)
    {
        array[index] = atoi(line);
        index++;
    }

    fclose(fp);
    if(line) {
        free(line);
    }

    SpreadSimulationSettings* settings = createSimSettings(
            array[0],
            array[1],
            array[2],
            array[3],
            array[4],
            array[5],
            array[6],
            array[7],
            array[8],
            array[9],
            array[10],
            array[11],
            array[12]
            );

    return settings;
}

void exportSettings(SpreadSimulationSettings* settings, char* filename)
{
    FILE* fp = fopen(filename, "w");

    if(fp == NULL){
        printf("Failed to create file.");
        return;
    }

    fprintf(fp, "Entity Count: %i\n", settings->entityCount);
    fprintf(fp, "Inital infected: %i\n", settings->initialInfected);
    fprintf(fp, "Mobile entities: %i\n", settings->mobileEntities);
    fprintf(fp, "Tests per tick: %i\n", settings->testsPerTick);

    fprintf(fp, "Hospital capacity: %i\n", settings->hospitalCapacity);
    fprintf(fp, "Tick until healed: %i\n", settings->ticksUntilHealed);
    fprintf(fp, "Infection chance on contact: %i\n", settings->chanceOfInfectionUponContact);
    fprintf(fp, "Survival chance: %i\n", settings->chanceOfSurviving);

    fprintf(fp, "Detection chance on test: %i\n", settings->chanceOfDetection);
    fprintf(fp, "Influence radius: %i\n", settings->influenceRadius);
    fprintf(fp, "Active distancing: %i\n", settings->activeDistancing);
    fprintf(fp, "Space: %i * %i\n", settings->confinedSpaceX, settings->confinedSpaceY);

    fclose(fp);
}