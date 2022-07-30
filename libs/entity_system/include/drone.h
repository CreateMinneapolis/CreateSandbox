#ifndef DRONE_H_
#define DRONE_H_

#include "./interfaces/entity.h"
#include "vector3.h"

/**
 * @brief Drone class that controls the functionality of the drone entity
 */
class Drone : public IEntity {
public:
    /**
     * @brief Default constructor. Takes a JsonObject of the entities details and assigns it for the object
     * @param[in] obj A JsonObject of all the drones details
     */
    Drone(JsonObject obj);
    /**
     * @brief Destructor
     */
    ~Drone();
    /**
     * @brief Gets details of the drone
     * @returns details of drones in a JsonObject
     */

    JsonObject GetDetails() const { return details; }
    /**
     * @brief Update function for the specific drone itself
     * @param[in] dt delta time! change in time from the last time the Update function was called
     */
    void Update(double dt);
    /**
     * @brief Sets drones velocity
     * @param[in] velocity new velocity for the drone
     */
    void SetVelocity(double* velocity);
    /**
     * @brief Gets drone position
     * @param[in] index returns the position of what index is sent in ?? makes no sense change this if its even a function we need
     */
    double GetPosition(int index) const { return position[index]; }
    /**
     * @brief Gets drone direction
     * @param[in] index This does nothing, will probably remove this later
     */
    double GetDirection(int index) const { return 0; }
    /**
     * @brief Sets drones position
     * @param[in] position New position for the drone
     */
    void SetPosition(double* position);
    /**
     * @brief Removing the copy constructor and assignment operator
     * so that drones cannot be copied.
     * @param[in] drone Another instance of a drone
     */
    Drone(const Drone& drone) = delete;


private:
/**
 * @brief Details of the drone entity from when it was first initalized like name, inital postion, initial velocity, and id
 */
    JsonObject details;
    /**
 * @brief Drones position
 */
    Vector3 position;
    /**
 * @brief Drones velocity
 */
    Vector3 velocity;

};

#endif
