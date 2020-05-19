/**
 * @file
 * Statistics for simulations
 *
 * @author cherrysrc
 * @data 19.05.2020
 * @copyright MIT-License
 */

#ifndef SPREADSIMREVIVED_SIMULATORSTATS_H
#define SPREADSIMREVIVED_SIMULATORSTATS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/**
 * @struct SimulatorStats
 * @brief Struct holding all information of statistical value
 */
typedef struct
{
    int tick;

    int susceptible;
    int infected;

    int cured;
    int dead;

    int hospitalized;

    float basicReproductionNumber; //R0
    float effectiveReproductionNumber; //Re
} SimulatorStats;

/**
 * Creates a SimulatorStats object
 * @param Susceptible the initial number of susceptible
 * @param Infected the inital number of infected
 * @return the created SimulatorStats object
 */
SimulatorStats createStats(int Susceptible, int Infected);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_SIMULATORSTATS_H
