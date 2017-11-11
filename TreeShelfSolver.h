//
// Created by Kuba on 05.11.2017.
//

#ifndef AAL_TREESHELF_H
#define AAL_TREESHELF_H


#include <map>
#include "Solver.h"

class TreeShelfSolver : public Solver {
public:
    TreeShelfSolver() = default;
    ~TreeShelfSolver() override = default;
    void arrange(CuboidContainer& container) override;
};


#endif //AAL_TREESHELF_H
