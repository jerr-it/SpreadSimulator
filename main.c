#include <stdio.h>
#include "SpreadSimulator.h"

int main()
{
    printf("Hello, World!\n");

    SpreadSimulator* simulator = createSpreadSimulator(
        900,                     /*samples*/
        5,                       /*initial infected*/
        850,                     /*mobile entities*/
        200,                     /*hospital capacity*/
        50,                      /*tests per tick*/
        450,                     /*ticks until healed/dead*/
        20,                      /*chance of infection upon contact*/
        50,                      /*chance of surviving*/
        50,                      /*detection chance, chance of an infected being found upon testing*/
        5,                       /*radius of influence (in pixels)*/
        createVector(600, 600)); /*Area of movement*/

    for (int i = 0; i < 120; i++)
    {
        printf("Unaffected: %i, Infected: %i, Cured: %i, Dead: %i \n", simulator->unaffected, simulator->infected, simulator->cured, simulator->dead);
        tick(simulator);
    }

    freeSpreadSimulator(simulator);

    return(0);
}
