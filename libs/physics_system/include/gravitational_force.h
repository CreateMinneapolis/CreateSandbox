#ifndef GRAVITATIONAL_FORCE_H
#define GRAVITATIONAL_FORCE_H
#include <iostream>
#include "./interfaces/IPhysicsSystem.h"
#include "./force.h"


/**
 * @brief Gravity!
 */
class GravitationalForce : public Force {
public:
    /**
     * @brief Default constructor.
     */
    GravitationalForce();
    /**
     * @brief Adds Force
     */
    void AddForces();


};



#endif