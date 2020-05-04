#ifndef SPREADSIMREVIVED_MEDICALCOMPONENT_H
#define SPREADSIMREVIVED_MEDICALCOMPONENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    int ticksSinceInfection;

    int infectionChance;
    int survivalChance;
    int detectionChance;

    bool isInfected;
    bool isMobile;
    bool isCured;
    bool isDead;
    bool isInHospital;

    double infectionRadius;
} MedicalComponent;

MedicalComponent*
createMedicalComponent(bool infected, bool mobile, int infChance, int survChance, int detectChance, double infRadius);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_MEDICALCOMPONENT_H
