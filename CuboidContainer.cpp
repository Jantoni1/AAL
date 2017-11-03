//
// Created by Kuba on 03.11.2017.
//

#include "CuboidContainer.h"

CuboidContainer::CuboidContainer(double length, double depth)
        : length_(length)
        , depth_(depth)
{
    height_ = 0;
}

CuboidContainer::CuboidContainer() {
    length_ = 0;
    height_ = 0;
    depth_ = 0;
}

double CuboidContainer::getLength() const {
    return length_;
}

double CuboidContainer::getHeight() const {
    return height_;
}

double CuboidContainer::getDepth() const {
    return depth_;
}

std::istream &operator>>(std::istream &str, CuboidContainer &data) {
    str >> data.length_;
    str >> data.depth_;
}

void CuboidContainer::setHeight(double height) {
    height_ = height;
}

CuboidContainer::CuboidContainer(const CuboidContainer &other)
        : outside_(other.outside_)
        , emplaced_(other.emplaced_)
        , length_(other.length_)
        , depth_(other.depth_)
{
}

const std::vector<Cuboid> &CuboidContainer::getEmplaced_() const {
    return emplaced_;
}

