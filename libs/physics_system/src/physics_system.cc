#include "./../include/physics_system.h"
#include <stdio.h>
#include <stdlib.h> 

int PhysicsSystem::AddEntity(std::string name, double* position, double* velocity){
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

    return 1;
}
        
PhysicsSystem::Vec* PhysicsSystem::GetPositionVectorOfEntity(std::string entityName) {
    int firstIndexOfEntity = entityPositionsInVector[entityName][0];

    Vec* entityPosition = (Vec*) malloc(sizeof(Vec)*2);
    
    entityPosition[0] = positionVector[firstIndexOfEntity];
    entityPosition[1] = positionVector[firstIndexOfEntity + 1];
    entityPosition[2] = positionVector[firstIndexOfEntity + 2];

    return entityPosition;
}

PhysicsSystem::Vec* PhysicsSystem::GetPositionVector() {
    return positionVector;
}

PhysicsSystem::Vec* PhysicsSystem::GetVelocityVector() {
    return velocityVector;
}

PhysicsSystem::Vec PhysicsSystem::GetForceAccumulator() {
    return forceAccumulator;
}

void PhysicsSystem::UpdateSimulationTime(double dt){
    simulationTime = simulationTime + dt;
}

void PhysicsSystem::CircleForce() {
    positionVector[0] = 0.5 * std::cos(simulationTime);
    positionVector[2] = 0.5 * std::sin(simulationTime);
}