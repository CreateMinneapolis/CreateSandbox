#ifndef DRONE_H_
#define DRONE_H_

#include "./interfaces/entity.h"
#include "vector3.h"

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
class Drone : public IEntity {
public:
    // Drones are created with a name
    Drone(JsonObject obj);
    // Destructor
    ~Drone();
    // Gets the drone position
    double GetPosition(int index) const { return position[index]; }

    double GetDirection(int index) const { return 0; }

    JsonObject GetDetails() const { return details; }

    // Updates the drone's position
    void Update(double dt);
    // Sets the drone's velocity
    void SetVelocity(double* velocity);
    // Rotates a drone
    void Rotate(double angle);

    // Removing the copy constructor and assignment operator
    // so that drones cannot be coppied.
    Drone(const Drone& drone) = delete;

    Drone& operator=(const Drone& drone) = delete;

private:
    JsonObject details;
    Vector3 position;
    Vector3 velocity;
    double droneTime;
};

#endif
