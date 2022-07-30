#include "./../include/physics_system.h"
#include <stdio.h>
#include <stdlib.h> 

int PhysicsSystem::AddEntity(std::string name, double* position, double* velocity){
    std::cout << "Adding " << name << " Entity" << std::endl;

    for(int i = 0; i < 3; i++){
        positionVector[vectorLength + i] = position[i];
        velocityVector[vectorLength + i] = velocity[i];
    }

    std::vector<int> posInVectors = {vectorLength, vectorLength + 2};
    vectorLength = vectorLength + 1;
    entityPositionsInVector.insert(std::pair<std::string, std::vector<int>>(name, posInVectors));
    free(position);

    return 1;
}
        
PhysicsSystem::Vec* PhysicsSystem::GetPositionVectorOfEntity(std::string entityName) {
    int firstIndexOfEntity = entityPositionsInVector[entityName][0];

    Vec* entityPosition = (Vec*) malloc(sizeof(Vec)*2);
    for(int i = 0; i < 3; i++){
        entityPosition[i] = positionVector[firstIndexOfEntity + i];
    }
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