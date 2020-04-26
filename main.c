#include <stdio.h>
#include "src/SpreadSimulator.h"

int main()
{
    printf("Hello, World!\n");

    SpreadSimulationSettings* settings = createSimSettings(
        900,
        5,
        850,
        200,
        50,
        450,
        20,
        50,
        50,
        5,
        true,
        600,
        600);

    //SpreadSimulationSettings* settings = loadSettings("settings.txt");
    //saveSettings(settings, "settings.txt");
    //exportSettings(settings, "export.txt");

    SpreadSimulator* simulator = createSpreadSimulator(settings);

    for (int i = 0; i < 120; i++)
    {
        printf("Unaffected: %i, Infected: %i, Cured: %i, Dead: %i \n", simulator->unaffected, simulator->infected, simulator->cured, simulator->dead);
        tick(simulator);
    }

    freeSpreadSimulator(simulator);

    return(0);
}
