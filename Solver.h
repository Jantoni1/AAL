//
// Created by Kuba on 03.11.2017.
//

#ifndef AAL_CONTAINER_H
#define AAL_CONTAINER_H


#include "Cuboid.h"
#include "CuboidContainer.h"

class Solver {
private:


public:
    Solver() = default;
    virtual void arrange(CuboidContainer& array) = 0;
    virtual ~Solver() = default;
};


#endif //AAL_CONTAINER_H
