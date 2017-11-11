//
// Created by Kuba on 05.11.2017.
//

#include "TreeShelfSolver.h"
#include "TreeShelf.h"
void TreeShelfSolver::arrange(CuboidContainer &container) {
    double heightOffset = 0.0;
    std::vector<TreeShelf*> shelves;
    std::for_each(container.outside_.begin(), container.outside_.end(),
                  [&](Cuboid* cuboid) {turnShortestUp(cuboid, 0.0);});
    while(!container.outside_.empty()) {
        shelves.push_back(new TreeShelf(container.getLength(), container.getDepth(), heightOffset));
        auto it = std::remove_if(container.outside_.begin(), container.outside_.end(),
                                 [&](Cuboid* cuboid) -> bool { return shelves.back()->add(cuboid);});
        container.outside_.erase(it, container.outside_.end());
        heightOffset += shelves.back()->getCurrentHeight_();
        for (auto it : *shelves.back()) {
            if(it->cuboid_ != nullptr) {
                container.put(it->cuboid_);
            }
            it->cuboid_ = nullptr;
        }
    }
    container.setHeight(heightOffset);
    for(TreeShelf* treeShelf : shelves) {
        delete treeShelf;
    }
}
