//
// Created by Kuba on 04.11.2017.
//

#include "Shelf.h"

Shelf::Shelf(double maxDepth, double length, double heightOffset, double depthOffset)
        : maxDepth_(maxDepth)
        , maxLength_(length)
        , currentHeight_(0.0)
        , currentLength_(length)
        , currentDepth_(0.0)
        , heightOffset_(heightOffset)
        , depthOffset_(depthOffset)
{
}

bool Shelf::add(Cuboid* cuboid) {
    if(fits(*cuboid)) {
        put(cuboid);
        return true;
    }
    return false;
}

void Shelf::put(Cuboid* cuboid) {
    if(cuboid->getDepth() > currentDepth_) {
        currentDepth_ = cuboid->getDepth();
    }

    if(cuboid->getHeight() > currentHeight_) {
        currentHeight_ = cuboid->getHeight();
    }
    cuboid->setDisplacement({maxLength_ - currentLength_, heightOffset_, depthOffset_});
    cuboid->mapVertices();
    currentLength_ -= cuboid->getLength();
    content_.push_back(cuboid);
}

double Shelf::getCurrentHeight_() const {
    return currentHeight_;
}

double Shelf::getCurrentDepth_() const {
    return currentDepth_;
}

std::vector<Cuboid*>& Shelf::getContent_() {
    return content_;
}

bool Shelf::fits(Cuboid &cuboid) const {
    if(cuboid.getLength() > currentLength_ || cuboid.getDepth() > maxDepth_) {
        return true;
    }
    if(cuboid.getLength() <= maxDepth_ && cuboid.getDepth() <= currentLength_) {
        cuboid.rotateHorizontally();
        return true;
    }
    return false;
}

Shelf::~Shelf() {
    for(Cuboid* cuboid : content_) {
        delete cuboid;
    }
}
