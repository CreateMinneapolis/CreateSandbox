#include "./../include/drone.h"

#define PI 3.14159265

Drone::Drone(JsonObject obj) : details(obj) {
    // Drones have 3 components x,y,z
    JsonArray pos = obj["position"];
    position = Vector3(pos[0],pos[1],pos[2]);
    velocity = Vector3(1,1,1);
}

Drone::~Drone() {
    // Delete dynamically allocated variables
}

void Drone::SetVelocity(double* velocity) {
    //Copy the velocity data into the member variable array.
    for(int i = 0; i < 3; i++){
        this->velocity[i] = velocity[i];
    }
}

void Drone::SetPosition(double* position){
        for(int i = 0; i < 3; i++){
        this->position[i] = position[i];
    }
}
void Drone::Update(double dt) {
   return;
   
}
