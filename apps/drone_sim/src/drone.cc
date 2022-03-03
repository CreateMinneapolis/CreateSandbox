#include "drone.h"

Drone::Drone() {
    joystick[0] = 0;
    joystick[1] = 0;
    joystick[2] = 0;
    joystick[3] = 0;
    propSpeed[0] = 0;
    propSpeed[1] = 0;
    propSpeed[2] = 0;
    propSpeed[3] = 0;
}

void Drone::Update(double dt) {
    // Use Euler Integration to update the position of the drone
    // based on the direction of the joystick
    // e.g. position += joystick*dt

    // Update the propeller speed to show which propellers are moving
    // e.g. if moving left, the two right propellers are fast, and the two
    // left propellers are slow.

    // Optional: Use the joystick as an accelleration to update the velocity
    // and use the velocity to update a position.
    // e.g. acceleration += joystick;
    //      velocity += acceleration*dt
    //      position += velocity*dt

    // Optional: Add a directional wind force, using the accelleration (F=ma) to update the velocity.
}

double Drone::GetPosition(int index) {
    // Return the position (x=0, y=1, z=2) from your position vector
    // return position[index];
    return 0.0;
}

double Drone::GetPropellerSpeed(int index) {
    return propSpeed[index];
}

void Drone::SetJoystick(double x, double y, double z, double rotate) {
    joystick[0] = x;
    joystick[1] = y;
    joystick[2] = z;
    joystick[3] = rotate;
    std::cout << x << " " << y << " " << z << " " << rotate << std::endl;
}
