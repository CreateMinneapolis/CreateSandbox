#ifndef DRONE_APP_H_
#define DRONE_APP_H_

#include "controller.h"
#include "composite_factory.h"
#include "./../utils/json.h"
#include "physics_system.h"
#include <stdio.h>
#include <stdlib.h> 

/**
 ** @brief Models the simulation and handles the entities within them. Used to communicate with the web app and control the entities
 */
class SimulationModel : public PhysicsSystem {
public:
    /**
     * @brief Constructor for a simulation model. This gets instantiated in the web app.
     * @param[in] controller A controller 
     */
    SimulationModel(IController& controller);
    /**
     * @brief Takes a JsonObject from the web app and with that information models an entity within the SimulationModel, and then that entity can be used to 
     * control what it does in the web app
     * @param[in] entity A JsonObject of all the entity details
     */
    void CreateEntity(JsonObject& entity);
    /**
     * @brief This is where at all happens! This function gets constantly called and lets us update the entities properties that are then reflected back on the screen. Its basically
     * like the game loop. 
     */
    void Update(double dt);

private:
    /**
     * @brief controller
     */
    IController& controller;
    /**
     * @brief vector of all existing entities in the system
     */
    std::vector<IEntity *> entities;
    /**
     * @brief composite factory of all entity factories that exist
     */
    CompositeFactory compFactory;
};



#endif