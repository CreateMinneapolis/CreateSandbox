#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <map>
// Web application for displaying a drone
class PhysicsSystem  {
public:
    // Default constructor
    typedef double Vec;

    Vec* GetState();
    Vec* SetState();
    Vec* CalculateDerivative();
    Vec* AddForce();
    void AddEntity(std::string name, double* position) {
        std::cout << "Adding " << name << " Entity" << std::endl;
        positionVector[0] = position[0];
        positionVector[1] = position[1];
        positionVector[2] = position[2];
        std::vector<int> posInVectors = {endOfVectorPos + 1,endOfVectorPos + 4};
        endOfVectorPos = endOfVectorPos + 3;
        entityPositionsInVector.insert(std::pair<std::string, std::vector<int>>(name, posInVectors));
        free(position);

    }
    Vec* GetPositionVectorOfEntity(std::string entityName) {
        std::vector<int> getVectorIndex = entityPositionsInVector[entityName];
        Vec* entityPosition = (Vec*) malloc(sizeof(Vec)*3);
        entityPosition[0] = positionVector[getVectorIndex[0]];
        entityPosition[1] = positionVector[getVectorIndex[1]];
        entityPosition[2] = positionVector[getVectorIndex[2]];
        return entityPosition;
    }
    Vec* GetPositionVector() {
        return positionVector;
    }
    Vec* GetVelocityVector() {
        return velocityVector;
    }
    Vec GetForceAccumulator() {
        return forceAccumulator;
    }

    void SetTime(double dt){
        simulationTime = simulationTime + dt;
    }
    void CircleForce() {
        positionVector[0] = 0.5 * std::cos(simulationTime);
        positionVector[1] = 0.5 * std::sin(simulationTime);
    }

private:
    std::map<std::string, std::vector<int>> entityPositionsInVector;
    double simulationTime = 0;
    int endOfVectorPos = 0;
    Vec* positionVector = (Vec*) malloc(sizeof(Vec)*3); /* position Vector */
    Vec* velocityVector = (Vec*) malloc(sizeof(Vec)*3);; /* velocity Vector */
    Vec forceAccumulator; /* force accumulator */
};



#endif