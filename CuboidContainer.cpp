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
        : length_(other.length_)
        , depth_(other.depth_)
{
    for(Cuboid* cuboid : other.outside_) {
        outside_.push_back(new Cuboid(*cuboid));
    }
    for(Cuboid* cuboid: other.emplaced_) {
        emplaced_.push_back(new Cuboid(*cuboid));
    }
}

const std::vector<Cuboid*> &CuboidContainer::getEmplaced() const {
    return emplaced_;
}

void CuboidContainer::put(Cuboid *cuboid) {
    emplaced_.emplace_back(cuboid);
}

CuboidContainer::~CuboidContainer() {
    for(Cuboid* cuboid : outside_) {
        delete cuboid;
    }
    for(Cuboid* cuboid : emplaced_) {
        delete cuboid;
    }
}

std::ostream &operator<<(std::ostream &str, CuboidContainer &data) {
//    str << "Container's paremeters: length " << length_ << ", height: " << height_ << ", depth: " << depth_ <<std::endl << std::endl;
    str << data.length_ << " " << data.height_ << " " << data.depth_;
    for(Cuboid* cuboid : data.emplaced_) {
        str << std::endl << *cuboid;
    }
    str.flush();
}

