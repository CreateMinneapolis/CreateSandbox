#ifndef GRAVITATIONAL_FORCE_H
#define GRAVITATIONAL_FORCE_H
#include <iostream>
#include "./interfaces/IPhysicsSystem.h"
#include "./force.h"
// Web application for displaying a drone
class GravitationalForce : public Force {
public:
    // Default constructor
    GravitationalForce();
    void AddForces();


};



#endif