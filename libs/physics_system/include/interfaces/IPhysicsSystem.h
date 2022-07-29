#ifndef IPHYSICS_SYSTEM_H
#define IPHYSICS_SYSTEM_H
#include <iostream>

class IPhysicsSystem {
public:

    typedef double* Vec;

    virtual Vec* GetState() = 0;
    virtual Vec* SetState() = 0;
    virtual Vec* CalculateDerivative() = 0;
    virtual Vec* AddForce() = 0;

};



#endif