#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include <iostream>
#include "./interfaces/IPhysicsSystem.h"
// Web application for displaying a drone
class PhysicsSystem : public IPhysicsSystem {


public:
    // Default constructor
    PhysicsSystem() {};
    Vec* GetState();
    Vec* SetState();
    Vec* CalculateDerivative();
    Vec* AddForce();

private:
    Vec* positionVector; /* position Vector */
    Vec* velocityVector; /* velocity Vector */
    Vec* forceAccumulator; /* force accumulator */
};



#endif