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
    virtual void arrange(CuboidContainer& container) = 0;
    virtual ~Solver() = default;
    virtual void turnShortestUp(Cuboid* cuboid, double height) const final;
};


#endif //AAL_CONTAINER_H
