#ifndef DRONE_APP_H_
#define DRONE_APP_H_

#include "controller.h"
#include "composite_factory.h"
#include "./../utils/json.h"

// Web application for displaying a drone
class SimulationModel {
public:
    // Default constructor
    SimulationModel(IController& controller);
    void CreateEntity(JsonObject& entity);
    void Update(double dt);

private:
    IController& controller;
    std::vector<IEntity *> entities;
    CompositeFactory compFactory;
};



#endif