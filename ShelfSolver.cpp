//
// Created by Kuba on 04.11.2017.
//

#include "ShelfSolver.h"
#include "Shelf.h"

void ShelfSolver::arrange(CuboidContainer &container) {
    double newHeight = 0.0;
    double currentHeight = 0.0;
    double length = container.getLength();
    double currentDepth = container.getDepth();
    std::for_each(container.outside_.begin(), container.outside_.end(), [&](Cuboid* cuboid) {
            turnShortestUp(cuboid, 0.0);
            while(cuboid->getLength() > container.getLength() || cuboid->getDepth() > container.getDepth()) {
                cuboid->rotate();
            }});
    while(!container.outside_.empty()) {
        Shelf shelf(currentDepth, length, currentHeight, container.getDepth() - currentDepth);
        auto it = std::remove_if(container.outside_.begin(), container.outside_.end(), [&](Cuboid* cuboid) -> bool { return shelf.add(cuboid);});
        container.outside_.erase(it, container.outside_.end());
        if(shelf.getContent_().empty()) {
            length = container.getLength();
            currentDepth = container.getDepth();
            currentHeight += newHeight;
            newHeight = 0.0;
        }
        else {
            for(Cuboid* cuboid : shelf.getContent_()) {
                container.put(cuboid);
            }
            shelf.getContent_().clear();
            if(shelf.getCurrentHeight_() > newHeight) {
                newHeight = shelf.getCurrentHeight_();
            }
            currentDepth -= shelf.getCurrentDepth_();
        }
    }
    container.setHeight(newHeight);
}
