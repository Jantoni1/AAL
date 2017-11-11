//
// Created by Kuba on 04.11.2017.
//

#ifndef AAL_SHELF_H
#define AAL_SHELF_H


#include "Cuboid.h"

class Shelf {
private:
    double maxDepth_;
    double maxLength_;
    double currentHeight_;
    double currentDepth_;
    double currentLength_;
    double heightOffset_;
    double depthOffset_;
    std::vector<Cuboid*> content_;

    void put(Cuboid* cuboid);

public:
    Shelf(double maxDepth, double length, double heightOffset, double depthOffset);

    ~Shelf();

    bool add(Cuboid* cuboid);

    double getCurrentHeight_() const;

    double getCurrentDepth_() const;

    std::vector<Cuboid*>& getContent_();

    bool fits(Cuboid& cuboid) const;
};



#endif //AAL_SHELF_H
