#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <vector>
#include <cmath>
#include <map>

/**
 * @brief Physics engine for controlling how all entities should act in the simulation
 */
class PhysicsSystem  {
public:

    typedef double Vec;

    /**
     * @brief Calculates the derivative of the physics system
     */
    int CalculateDerivative();
    /**
     * @brief Adds a new force
     * @return 1 = success 0 = fail
     */
    int AddForce();

    /**
     * @brief Takes an entity from the EntitySystem and adds it to the physics system
     * @param[in] entityName Name of the entity that can then be used in the map
     * @param[in] position initial position of the entity
     * @param[in] velocity initial velocity of the entity
     */
    int AddEntity(std::string entityName, double* position, double* velocity);
    /**
     * @brief Takes an entity from the EntitySystem and adds it to the physics system
     * @param[in] entityName Name of the entity that can then be used to look up where it is in the vectors
     * @return Vec* of given entities position
     */
    Vec* GetPositionVectorOfEntity(std::string entityName);

    /**
     * @return returns position vector
     */
    Vec* GetPositionVector();
    /**
     * @return returns velocity vector
     */
    Vec* GetVelocityVector();
    /**
     * @return returns Force Accumulator vector
     */
    Vec GetForceAccumulator();

    /**
     * @brief takes in delta time and updates the simulation time
     */
    void UpdateSimulationTime(double dt);
    /**
     * @brief spins drone in circle. Used to show that the drone on the screen uses these vectors. Delete later
     */
    void CircleForce();

private:
    /**
     * @brief This map takes the name of the entity and returns the first and last index of where it is in the vectors
     */
    std::map<std::string, std::vector<int>> entityPositionsInVector;
    /**
     * @brief simulation time, is always up to date with the simulation running
     */
    double simulationTime = 0;
    /**
     * @brief length of all the vectors
     */
    int vectorLength = 0;
    /**
     * @brief vector of all entities positions
     */
    Vec* positionVector = (Vec*) malloc(sizeof(Vec)*30); 
    /**
     * @brief vector of all entities velocities
     */
    Vec* velocityVector = (Vec*) malloc(sizeof(Vec)*30);
    /**
     * @brief vector of all forces enacting on the vectors
     */
    Vec* forceVector = (Vec*) malloc(sizeof(Vec)*30);
    /**
     * @brief the force accumulator
     */
    Vec forceAccumulator;

};



#endif