//
// Created by Kuba on 03.11.2017.
//

#ifndef AAL_NAIVESOLVER_H
#define AAL_NAIVESOLVER_H


#include "Solver.h"

class NaiveSolver: public Solver{
private:

public:

    NaiveSolver() = default;
    void arrange(CuboidContainer& container) override;
    void turnShortestUp(Cuboid& cuboid, double height) const;
     ~NaiveSolver() override = default;

};


#endif //AAL_NAIVESOLVER_H
