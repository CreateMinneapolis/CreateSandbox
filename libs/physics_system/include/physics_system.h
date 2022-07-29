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
    //Give the name and initial position of the entity, then it will be put into the 
    //physics system and reflected in the main vectors
    void AddEntity(std::string name, double* position, double* velocity) {
        std::cout << "Adding " << name << " Entity" << std::endl;

        positionVector[vectorLength] = position[0];
        positionVector[vectorLength + 1] = position[1];
        positionVector[vectorLength + 2] = position[2];
        
        velocityVector[vectorLength] = velocity[0];
        velocityVector[vectorLength + 1] = velocity[1];
        velocityVector[vectorLength + 2] = velocity[2];

        std::vector<int> posInVectors = {vectorLength, vectorLength + 2};
        vectorLength = vectorLength + 1;
        entityPositionsInVector.insert(std::pair<std::string, std::vector<int>>(name, posInVectors));
        free(position);

    }
    //Return the position of the entity name passed in
    Vec* GetPositionVectorOfEntity(std::string entityName) {
        int firstIndexOfEntity = entityPositionsInVector[entityName][0];

        Vec* entityPosition = (Vec*) malloc(sizeof(Vec)*2);
       
        entityPosition[0] = positionVector[firstIndexOfEntity];
        entityPosition[1] = positionVector[firstIndexOfEntity + 1];
        entityPosition[2] = positionVector[firstIndexOfEntity + 2];

       // std::cout << getVectorIndex[0] << " " << getVectorIndex[1] << " " << getVectorIndex[2] << std::endl;
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

    //Gets the delta time coming in from the simulation model and updates the time
    //for the physics model
    void SetTime(double dt){
        simulationTime = simulationTime + dt;
    }
    //test, this shows that the position vector can be updated in the physics system 
    //and then that will correctly update the drone in the browser
    void CircleForce() {
        positionVector[0] = 0.5 * std::cos(simulationTime);
        positionVector[2] = 0.5 * std::sin(simulationTime);
    }

private:
    //This will map the name of the entity to first and last index of where it would be
    //in the position or velocity vector
    std::map<std::string, std::vector<int>> entityPositionsInVector;
    double simulationTime = 0;
    //length not the last index
    int vectorLength = 0;
    Vec* positionVector = (Vec*) malloc(sizeof(Vec)*30); /* position Vector */
    Vec* velocityVector = (Vec*) malloc(sizeof(Vec)*30);; /* velocity Vector */
    Vec* forceVector = (Vec*) malloc(sizeof(Vec)*30);; /* force Vector */
    Vec forceAccumulator; /* force accumulator */

    //Note, because these vectors are only malloc to 30, that means the system right now only 
    //Supports 10 entities. Later I want to make those vectors dynamic and be able to resize when
    // an entity is added and it goes over what ever limit we put at it first so it can support
    // as many entities that we want
};



#endif