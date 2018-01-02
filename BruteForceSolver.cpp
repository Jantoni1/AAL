//
// Created by Kuba on 22.12.2017.
//

#include "BruteForceSolver.h"

using Corner = CornerContainer::Corner;

void BruteForceSolver::arrange(CuboidContainer &container) {
    setup(container);
    do {
        for(std::pair<int, Cuboid*>& pair : cuboidPermutation) {
            currentPermutation.emplace_back(pair.second);
        }
        cuboidIterator = new std::vector<Cuboid*>::iterator(currentPermutation.begin());
        emplaceNextCuboid();
        delete cuboidIterator;
        currentPermutation.clear();

    } while(std::next_permutation(cuboidPermutation.begin(), cuboidPermutation.end()));
    clear();
}

void BruteForceSolver::emplaceNextCuboid() {
    if(allPlaced()) {
        return;
    }
    Cuboid& cuboid = ***cuboidIterator;
    for(Corner* corner : cornerContainer) {
        if(corner->isEmpty()) {
            for(int i = 0; i < Cuboid::getMaxRotations(); ++i) {
                cuboid.rotate();
                if(putCuboidInCorner(cuboid, *corner)) {
                    ++(*cuboidIterator);
                    emplaceNextCuboid();
                    eraseCuboid(cuboid, *corner);
                    --(*cuboidIterator);
                }
            }
        }
    }
}

void BruteForceSolver::setup(CuboidContainer &container) {
    this->container = &container;
    cornerContainer.createCorners(container);
    minHeight = std::numeric_limits<double>::max();
    for(Cuboid* cuboid : container.outside_) {
        cuboidPermutation.emplace_back(std::make_pair(cuboidPermutation.size(), cuboid));
    }
}

void BruteForceSolver::clear() {
    container->setHeight(minHeight);
    for(auto* cuboid : container->outside_) {
        delete cuboid;
    }
    container->outside_.clear();
    for( auto* cuboid : solution) {
        container->put(cuboid);
    }
    solution.clear();
    cornerContainer.clear();
    currentPermutation.clear();
    cuboidPermutation.clear();
}

bool BruteForceSolver::allPlaced() {
    if(*cuboidIterator == currentPermutation.end()) {
        double maxHeight = 0.0D;
        for(const auto* cuboid : currentPermutation) {
            maxHeight = std::max(std::get<1>(cuboid->getCenter()) + cuboid->getHeight()/2, maxHeight);
        }
        if(minHeight > maxHeight) {
            minHeight = maxHeight;
            for(auto* cuboid : solution) {
                delete cuboid;
            }
            solution.clear();
            for(const auto* cuboid : currentPermutation) {
                solution.emplace_back(new Cuboid(*cuboid));
            }
        }
        return true;

    }
    return false;
}

bool BruteForceSolver::putCuboidInCorner(Cuboid &cuboid, CornerContainer::Corner &corner) {
    if(!moveToCorner(cuboid, corner)) {
        return false;
    }
    for(auto iterator = currentPermutation.begin(); iterator != *cuboidIterator; ++iterator) {
        if(cuboidIntersectionCheck(**iterator, ***cuboidIterator)) {
            return false;
        }
    }
    corner.addCuboid(&cuboid);
    return true;
}

bool BruteForceSolver::moveToCorner(Cuboid &cuboid, CornerContainer::Corner &corner) {
    std::vector<double> displacement = {0.0, 0.0, 0.0};
    if(corner.position_ == CornerContainer::FRONT_RIGHT || corner.position_ == CornerContainer::BACK_RIGHT) {
        displacement[0] = corner.x_ - cuboid.getLength();
    }
    else {
        displacement[0] = corner.x_;
    }
    displacement[1] = corner.y_;
    if(corner.position_ == CornerContainer::BACK_LEFT  || corner.position_ == CornerContainer::BACK_RIGHT) {
        displacement[2] = corner.z_ - cuboid.getDepth();
    }
    else {
        displacement[2] = corner.z_;
    }
    // Check if the cuboid still fits in the box
    if(   displacement[0] < 0 || displacement[0] + cuboid.getCoordinate(0) > container->getLength()+ 0.00001
       || displacement[2] < 0 || displacement[2] + cuboid.getCoordinate(2) > container->getDepth() + 0.00001) {
        return false;
    }
    cuboid.setDisplacement(displacement);
    return true;
}

bool BruteForceSolver::cuboidIntersectionCheck(Cuboid &cuboid1, Cuboid &cuboid2) {
    const auto& center1 = cuboid1.getCenter();
    const auto& center2 = cuboid2.getCenter();
    return fabs(std::get<0>(center2) - std::get<0>(center1)) < (cuboid2.getLength()/2 + cuboid1.getLength()/2)
    &&     fabs(std::get<1>(center2) - std::get<1>(center1)) < (cuboid2.getHeight()/2 + cuboid1.getHeight()/2)
    &&     fabs(std::get<2>(center2) - std::get<2>(center1)) < (cuboid2.getDepth() /2 + cuboid1.getDepth() /2);
}

void BruteForceSolver::eraseCuboid(Cuboid &cuboid, CornerContainer::Corner &corner) {
    corner.clear();
    corner.cuboid = nullptr;
}

BruteForceSolver::BruteForceSolver()
    :   minHeight(std::numeric_limits<double>::max())
    ,   container(nullptr)
    ,   cuboidIterator(nullptr)
{

}
