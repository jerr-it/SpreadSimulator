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

//1 entity count
//2 initial infected
//3 initial mobile
//4 hospital capacity
//5 tests per tick
//6 ticks until expiration
//7 infection chance
//8 survival chance
//9 detection chance
//10 influence radius
//11 active distancing
//12 central locations count
//13 width
//14 height
//15 number of iterations
//16 number of threads
int main(int argc, char **argv)
{
    if(argc != 17) return 1;

    SimulationSettings iSettings = createSettings(
            atoi(argv[1]),
            atoi(argv[2]),
            atoi(argv[3]),
            atoi(argv[4]),
            atoi(argv[5]),
            atoi(argv[6]),
            atoi(argv[7]),
            atoi(argv[8]),
            atoi(argv[9]),
            atoi(argv[10]),
            atoi(argv[11]),
            atoi(argv[12]),
            atoi(argv[13]),
            atoi(argv[14])
            );

    /*
    SimulationSettings settings = createSettings(
            5000,
            5,
            4750,
            200,
            10,
            450,
            20,
            50,
            50,
            5,
            true,
            4,
            600, 600);
            */

    //Save and load settings of binary format
    //SimulationSettings* settings = loadSettings("settings.bin");
    //saveSettings(settings, "settings.bin");

    //Export to a human readable format:
    //exportSettings(settings, "exportSettings.txt");

    SpreadSimulator simulator = createSimulator(&iSettings, atoi(argv[16]));


    for (int i = 0; i < atoi(argv[15]); i++)
    {
        tick(&simulator);

        printStatsRaw(&simulator);
    }

    cleanup(&simulator);

    return (0);
}
