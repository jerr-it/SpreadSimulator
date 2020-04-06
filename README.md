![C](https://img.shields.io/badge/-Language-blue?style=for-the-badge&logo=c)
# SpreadSimulator
A Simulation of the spread and containment of infections
## How to use
Include Header:
```c
#include "SpreadSimulator.h"
```
Create settings for your simulation:
```c
SpreadSimulationSettings* settings = createSimSettings(
        900,    /*samples*/
        5,      /*initial infected*/
        850,    /*mobile entities*/
        200,    /*hospital capacity*/
        50,     /*tests per tick*/
        450,    /*ticks until healed/dead*/
        20,     /*chance of infection upon contact*/
        50,     /*chance of surviving*/
        50,     /*detection chance, chance of an infected being found upon testing*/
        5,      /*radius of influence (in pixels)*/
        true,   /*enable active distancing*/
        600,    /*Area of movement width*/
        600);   /*Area of movement height*/
```
Or load an existing configuration:
```c
SpreadSimulationSettings* settings = loadSettings("settings.txt");
```

Create a SpreadSimulator:
```c
SpreadSimulator* simulator = createSpreadSimulator(settings);
```  
The values related to a probability should be between 0-100.  
Run the simulator by one step using
```c
tick(simulator)
```
Running 120 ticks and logging the simulator values:
```c
for (int i = 0; i < 120; i++)
{
    printf("Unaffected: %i, Infected: %i, Cured: %i, Dead: %i \n", simulator->unaffected, simulator->infected, simulator->cured, simulator->dead);
    tick(simulator);
}
```
Save your settings to a file for later use:
```c
saveSettings(settings, "settings.txt");
```
You also have the option to save a more human-readable file:
```c
exportSettings(settings, "export.txt");
```
Dont forget to free afterwards to avoid memory leaks
```c
freeSpreadSimulator(simulator);
free(settings);
```
## How it works
In the following text the phrase within parenthesis will be a reference to above code snippets comments.  
The simulator creates a given number of entities(samples) within a confined space(Area of movement).  
Each of them is given a randomized motion vector, which is added to their position every tick.   
A number of them will be infected at the start(initial infected).  
A number of them will be able to move around(mobile entities).
If one hits the border it'll invert its x/y movement component to stay within the confined space.  
If another entity passes within a given radius(radius of influence in pixels), it'll get infected by a certain probability(chance of infection upon contact).  
When an entity gets infected a timer will start. As soon as this timer runs out, the entity will either survive or die by a certain percentage(chance of surviving).  
The hospital capacity(hospital capacity) determines how many hospital slots are available to the infected.  
Each tick a number of random entities(tests per tick) will be tested and detected using a certain probability(detection chance).  
In the case of an entity getting a positive test result, he won't be able to move anymore and its chance of surviving is set to 90%.
If active social distancing is set to true, the entities will try actively try to avoid each other.
