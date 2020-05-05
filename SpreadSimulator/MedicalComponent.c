#include "MedicalComponent.h"

MedicalComponent
createMedicalComponent(bool infected, bool mobile, int infChance, int survChance, int detectChance, double infRadius)
{
    MedicalComponent component ;

    component.ticksSinceInfection = 0;

    component.infectionChance = infChance;
    component.survivalChance = survChance;
    component.detectionChance = detectChance;

    component.isInfected = infected;
    component.isMobile = mobile;
    component.isCured = false;
    component.isDead = false;
    component.isInHospital = false;

    component.infectionRadius = infRadius;

    return component;
}
