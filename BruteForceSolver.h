//
// Created by Kuba on 22.12.2017.
//

#ifndef AAL_BRUTEFORCESOLVER_H
#define AAL_BRUTEFORCESOLVER_H


#include "CuboidContainer.h"
#include "Solver.h"
#include "CornerContainer.h"
#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>
#include <iterator>


class BruteForceSolver : public Solver {
public:
    BruteForceSolver();
    ~BruteForceSolver() override = default;
    void arrange(CuboidContainer& container) override;
    void emplaceNextCuboid();
    void setup(CuboidContainer& container);
    void clear();
    bool allPlaced();
    bool putCuboidInCorner(Cuboid& cuboid, CornerContainer::Corner& corner);
    bool moveToCorner(Cuboid &cuboid, CornerContainer::Corner &corner);
    bool cuboidIntersectionCheck(Cuboid& cuboid1, Cuboid& cuboid2);
    void eraseCuboid(Cuboid& cuboid, CornerContainer::Corner& corner);
private:
    std::vector<Cuboid*> currentPermutation;
    CornerContainer cornerContainer;
    double minHeight;
    std::vector<std::pair<int, Cuboid*> > cuboidPermutation;
    std::vector<Cuboid*> solution;
    CuboidContainer* container;
    std::vector<Cuboid*>::iterator* cuboidIterator;
};


#endif //AAL_BRUTEFORCESOLVER_H
