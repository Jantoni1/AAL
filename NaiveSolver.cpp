//
// Created by Kuba on 03.11.2017.
//

#include "NaiveSolver.h"



void NaiveSolver::arrange(CuboidContainer& container) {
    double height = 0.0;
    std::vector<Cuboid*>& cuboids = container.outside_;

    std::for_each(cuboids.begin(), cuboids.end(), [&](Cuboid* cuboid) -> void {
        turnShortestUp(cuboid, height); container.put(cuboid);
        height += cuboid->getHeight();
        container.setHeight(container.getHeight() + cuboid->getHeight());
    });
    container.outside_.clear();
}


