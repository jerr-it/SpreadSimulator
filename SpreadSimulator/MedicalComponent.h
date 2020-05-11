/**
 * @file
 * Struct keeping track of an entites health situation
 *
 * @author cherrysrc
 * @data 11.05.2020
 * @copyright MIT-License
 */

#ifndef SPREADSIMREVIVED_MEDICALCOMPONENT_H
#define SPREADSIMREVIVED_MEDICALCOMPONENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

/**
 * @struct MedicalComponent
 * @brief Struct keeping track of an entities health
 */
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

/**
 * Creates a MedicalComponent from given parameters
 * @param infected true/false, whether or not this entity is infected
 * @param mobile true/false, whether or not this entity is mobile
 * @param infChance (0-100) chance of infection
 * @param survChance (0-100) chance of survival
 * @param detectChance (0-100) chance of detection
 * @param infRadius radius of influence
 * @return The created MedicalComponent
 */
MedicalComponent
createMedicalComponent(bool infected, bool mobile, int infChance, int survChance, int detectChance, double infRadius);

#ifdef __cplusplus
}
#endif

#endif //SPREADSIMREVIVED_MEDICALCOMPONENT_H
