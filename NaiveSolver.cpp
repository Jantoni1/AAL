//
// Created by Kuba on 03.11.2017.
//

#include "NaiveSolver.h"



void NaiveSolver::arrange(CuboidContainer& container) {
    double height = 0.0;
    std::vector<Cuboid>& cuboids = container.outside_;
    std::cout<<"ELKO" <<std::endl;

    std::for_each(cuboids.begin(), cuboids.end(), [&](Cuboid& cuboid) -> void {
        std::cout<<cuboid.getHeight()<<std::endl;
        turnShortestUp(cuboid, height); container.put(cuboid);
        height += cuboid.getHeight();
        container.setHeight(container.getHeight() + cuboid.getHeight());
    });
}

void NaiveSolver::turnShortestUp(Cuboid& cuboid, double height) const {
    double min = std::min({cuboid.getLength(), cuboid.getHeight(), cuboid.getDepth()});
    while(cuboid.getHeight() != min) {
        cuboid.rotate();
    }
    cuboid.setDisplacement({0.0 ,height, 0.0});
}

