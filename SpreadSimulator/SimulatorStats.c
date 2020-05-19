#include "SimulatorStats.h"

SimulatorStats createStats(int susceptible, int infected)
{
    SimulatorStats stats;

    stats.tick = 0;

    stats.susceptible = susceptible;
    stats.infected = infected;

    stats.cured = 0;
    stats.dead = 0;

    stats.hospitalized = 0;

    stats.basicReproductionNumber = 0;
    stats.effectiveReproductionNumber = 0;

    return stats;
}
