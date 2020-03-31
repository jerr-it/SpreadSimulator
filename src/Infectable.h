//
// Created by jerrit on 31.03.20.
//

#ifndef SPREADSIM_INFECTABLE_H
#define SPREADSIM_INFECTABLE_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

typedef struct {
    int timeUnitSinceInfection;
    int timeUnitUntilEnd;

    int infectionChance;
    int survivalChance;
    int detectionChance;

    bool isInfected;
    bool isMobile;
    bool isCured;
    bool isDead;

    bool inHospital;
    double influenceRadius;
} Infectable;

Infectable* createInfectable(int tUSinceInfection, int tUUntilEnd,int infChance, int survChance, int detect, bool infected, bool mobil, double infRadius);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIM_INFECTABLE_H
