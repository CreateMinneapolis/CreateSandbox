#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <vector>
#include <iostream>


/// @brief A class built solely to handle 3D vector mathematics.
class Vec {
    public:
        std::vector<std::vector<double>> GetVector(){
            return mainVec;
        }
    private:
        std::vector<std::vector<double>> mainVec;
};

#endif  // Vec