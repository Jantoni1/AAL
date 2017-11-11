//
// Created by Kuba on 03.11.2017.
//

#include "Solver.h"

void Solver::turnShortestUp(Cuboid* cuboid, double height) const {
    double min = std::min({cuboid->getLength(), cuboid->getHeight(), cuboid->getDepth()});
    while(cuboid->getHeight() != min) {
        cuboid->rotate();
    }
    cuboid->setDisplacement({0.0 ,height, 0.0});
}
