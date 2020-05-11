/**
 * @file
 * Demonstrating the usage of SpreadSimulator
 *
 * @author cherrysrc
 * @date 11.05.2020
 * @copyright MIT-License
 */

/**
 * \mainpage SpreadSimulator Home
 * https://github.com/cherrysrc/SpreadSimulator
 */

#include "SpreadSimulator/SpreadSimulator.h"

#include <time.h>

int main()
{
    SimulationSettings settings = createSettings(
        5000,
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
        4,
        600, 600);

    //Save and load settings of binary format
    //SimulationSettings* settings = loadSettings("settings.bin");
    //saveSettings(settings, "settings.bin");

    //Export to a human readable format:
    //exportSettings(settings, "exportSettings.txt");

    SpreadSimulator simulator = createSimulator(&settings);

    clock_t start, end;

    for (int i = 0; i < 10000; i++)
    {
        //start = clock();
        tick(&simulator);
        //end = clock();

        //fprintf(stdout, "%ld\n", (end - start));
        printStats(&simulator);
    }

    cleanup(&simulator);

    return(0);
}
