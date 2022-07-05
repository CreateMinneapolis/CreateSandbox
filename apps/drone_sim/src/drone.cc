#include "./../include/drone.h"

#define PI 3.14159265

Drone::Drone(JsonObject obj) : details(obj) {
    // Drones have 3 components x,y,z
    JsonArray pos = obj["position"];

    position = Vector3(pos[0],pos[1],pos[2]);
    velocity = Vector3(200,200,200);

    droneTime = 0.0;
    
}

Drone::~Drone() {
    // Delete dynamically allocated variables
}

void Drone::SetVelocity(double* velocity) {
    // Copy the velocity data into the member variable array.
    // for(int i = 0; i < 3; i++){
    //     this->velocity[i] = velocity[i];
    // }
}

void Drone::Update(double dt) {
    droneTime += dt;
    position[0] = 0 + 1000 * std::cos(droneTime);
    position[2] = 0 + 1000 * std::sin(droneTime);
}

void Drone::Rotate(double angle) {
    // Rotates the drone by changing the velocity by a
    // specified angle.
    double x = velocity[0];
    double y = velocity[1];
    velocity[0] = x*std::cos(angle) - y*std::sin(angle);
    velocity[1] = x*std::sin(angle) + y*std::cos(angle);
}
