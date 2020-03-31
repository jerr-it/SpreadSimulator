#include "SpreadSimulator.h"

SpreadSimulator* createSpreadSimulator(SpreadSimulationSettings* settings){
    SpreadSimulator* sim = (SpreadSimulator*)calloc(1, sizeof(SpreadSimulator));

    sim->entityCount = settings->entityCount;
    sim->entities = (Entity**)calloc(settings->entityCount, sizeof(Entity*));

    for(int i = 0; i < settings->entityCount; i++)
    {
        bool infected = false;
        if(i < settings->initialInfected){
            infected = true;
        }

        bool mobile = false;
        if(i < settings->mobileEntities){
            mobile = true;
        }

        Infectable* inf = createInfectable(0, settings->ticksUntilHealed, settings->chanceOfInfectionUponContact, settings->chanceOfSurviving, settings->chanceOfDetection, infected, mobile, settings->influenceRadius);
        sim->entities[i] = createEntity(createVector(rand() % settings->confinedSpaceX, rand() % settings->confinedSpaceY), createVector(rand() % 5 - 2.5, rand() % 5 - 2.5), createVector(settings->confinedSpaceX, settings->confinedSpaceY), inf);
    }

    sim->cured = 0;
    sim->infected = settings->initialInfected;
    sim->dead = 0;
    sim->unaffected = settings->entityCount - settings->initialInfected;
    sim->hospitalCapacity = settings->hospitalCapacity;
    sim->hospitalized = 0;
    sim->testsPerTick = settings->testsPerTick;

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

void freeSpreadSimulator(SpreadSimulator* sim){
    for(int i = 0; i < sim->entityCount; i++){
        freeEntity(sim->entities[i]);
    }
    free(sim->entities);
    free(sim);
}