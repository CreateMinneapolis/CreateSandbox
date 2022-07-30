#ifndef DRONE_APP_H_
#define DRONE_APP_H_

#include "controller.h"
#include "composite_factory.h"
#include "./../utils/json.h"
#include "physics_system.h"
#include <stdio.h>
#include <stdlib.h> 
// Web application for displaying a drone
class SimulationModel : public PhysicsSystem {
public:
    // Default constructor
    SimulationModel(IController& controller);
    void CreateEntity(JsonObject& entity);
    void Update(double dt);

private:
    double simulationTime = 0;
    IController& controller;
    std::vector<IEntity *> entities;
    CompositeFactory compFactory;
};



#endif