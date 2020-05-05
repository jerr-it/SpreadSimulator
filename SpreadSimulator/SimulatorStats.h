#ifndef SPREADSIMREVIVED_SIMULATORSTATS_H
#define SPREADSIMREVIVED_SIMULATORSTATS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

// struct to simplify keeping track of simulation statistics
typedef struct
{
    int tick;

    int susceptible;
    int infected;

    int cured;
    int dead;

    int hospitalized;
} SimulatorStats;

SimulatorStats createStats(int Susceptible, int Infected);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_SIMULATORSTATS_H
