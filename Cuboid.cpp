//
// Created by Kuba on 03.11.2017.
//

#include "Cuboid.h"

Cuboid::Cuboid(double length, double height, double depth)
        : length_(length)
        , height_(height)
        , depth_(depth)
        , x_(length)
        , y_(height)
        , z_(depth)
{
    rotation_ = 0;
    displacement_ = {0.0 ,0.0 ,0.0};
}

void Cuboid::rotate() {
    double tmp = depth_;
    if(rotation_ % 2 == 1) {
        depth_ = length_;
        length_ = tmp;
    }
    else {
        depth_ = height_;
        height_ = tmp;
    }
    mapVertices();
    rotation_ = (rotation_ + 1) % NUMBER_OF_ROTATIONS;
}

void Cuboid::mapVertices() {
    x_ = length_ + displacement_[0];
    y_ = height_ + displacement_[1];
    z_ = depth_  + displacement_[2];
}

void Cuboid::rotate(int rotation) {
    while(rotation_ != rotation) {
        rotate();
    }
}

void Cuboid::setDisplacement(const std::vector<double>& displacement) {
    std::transform(displacement.begin(), displacement.end(), displacement_.begin(), [](double x) -> double {return x;});
    mapVertices();
}

std::istream &operator>>(std::istream &str, Cuboid &data) {
    str >> data.length_;
    str >> data.height_;
    str >> data.depth_;
    return str;
}

double Cuboid::getLength() const {
    return length_;
}

double Cuboid::getHeight() const {
    return height_;
}

double Cuboid::getDepth() const {
    return depth_;
}

Cuboid::Cuboid(const Cuboid &other) {
    length_ = other.length_;
    height_ = other.height_;
    depth_ = other.depth_;
    displacement_ = other.displacement_;
    rotation_ = other.rotation_;
    mapVertices();
}

Cuboid::Cuboid()
    : length_(0.0)
    , height_(0.0)
    , depth_(0.0)
{
    rotation_ = 0;
    displacement_ = {0.0 ,0.0 ,0.0};
}

Cuboid::Cuboid(Cuboid && other) noexcept
: length_(other.length_)
, height_(other.height_)
, depth_(other.depth_)
, rotation_(other.rotation_)
, displacement_(other.displacement_)
{}




