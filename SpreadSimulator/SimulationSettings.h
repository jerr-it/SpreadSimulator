/**
 * @file
 * File concerning simulation settings
 *
 * @author cherrysrc
 * @date 11.05.2020
 * @copyright MIT-License
 */

#ifndef SPREADSIMREVIVED_SIMULATIONSETTINGS_H
#define SPREADSIMREVIVED_SIMULATIONSETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * @struct SimulationSettings
 * @brief Struct containing all information concerning the settings of a simulation
 */
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

/**
 * Function for creating a settings object
 * @param EntityCount overall entity count
 * @param InitialInfected how many of the entities should be infected at start
 * @param InitialMobile how many of the entities should be mobile at start
 * @param HospitalCapacity whats the number of hospital beds
 * @param TestsPerTick tests executed per time unit
 * @param TicksUntilExpiration ticks until the patient either survives or dies
 * @param InfectionChance (0-100) chance an entity gets infected when hes in range of another infected entity
 * @param SurvivalChance (0-100) chance an entity survives the infection
 * @param DetectionChance (0-100) chance an infected enemy will revealed by a test
 * @param InfluenceRadius radius in which another entity can get infected
 * @param ActiveDistancing true/false whether entities should actively avoid each other
 * @param centralLocationsCount number of central locations to be simulated
 * @param DimX width of the available space
 * @param DimY height of the available space
 * @return the created settings object
 */
SimulationSettings
createSettings(int EntityCount, int InitialInfected, int InitialMobile, int HospitalCapacity, int TestsPerTick,
               int TicksUntilExpiration, int InfectionChance, int SurvivalChance, int DetectionChance,
               double InfluenceRadius, bool ActiveDistancing, int centralLocationsCount, int DimX, int DimY);

/**
 * Saves settings into a binary file
 * @param settings the targeted settings object
 * @param filename the filename in which the settings will be saved
 */
void saveSettings(SimulationSettings* settings, char* filename);

/**
 * Saves settings into a text file using a human readable format
 * @param settings the targeted settings object
 * @param filename the filename in which the settings should be saved
 */
void exportSettings(SimulationSettings* settings, char* filename);

/**
 * Load settings from a binary file
 * @param filename the desired filename
 * @return Settings object created from the given file
 */
SimulationSettings* loadSettings(char* filename);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_SIMULATIONSETTINGS_H
