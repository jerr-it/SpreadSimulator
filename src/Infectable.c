//
// Created by jerrit on 31.03.20.
//

#include "Infectable.h"

Infectable* createInfectable(int tUSinceInfection, int tUUntilEnd,int infChance, int survChance, int detectChance, bool infected, bool mobil, double infRadius, bool activeDist){
    Infectable* inf = (Infectable*)calloc(1, sizeof(Infectable));

    inf->timeUnitSinceInfection = tUSinceInfection;
    inf->timeUnitUntilEnd = tUUntilEnd;
    inf->infectionChance = infChance;
    inf->survivalChance = survChance;
    inf->isInfected = infected;
    inf->isMobile = mobil;
    inf->influenceRadius = infRadius;
    inf->isCured = false;
    inf->isDead = false;
    inf->inHospital = false;
    inf->detectionChance = detectChance;
    inf->activeDistancing = activeDist;

    return inf;
}