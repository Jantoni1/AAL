//
// Created by Kuba on 04.11.2017.
//

#ifndef AAL_SHELFSOLVER_H
#define AAL_SHELFSOLVER_H


#include "Solver.h"

class ShelfSolver: public Solver {
public:
    ShelfSolver() = default;
    ~ShelfSolver() override= default;
    void arrange(CuboidContainer& container) override;
};


#endif //AAL_SHELFSOLVER_H
