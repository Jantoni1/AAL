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
    if(rotation_ % 2 == 0) {
        depth_ = length_;
        length_ = tmp;
    }
    else {
        depth_ = height_;
        height_ = tmp;
    }
    rotation_ = (rotation_ + 1) % NUMBER_OF_ROTATIONS;
}

void Cuboid::rotateBack() {
    double tmp = depth_;
    if(rotation_ %2 == 0) {
        depth_ = height_;
        height_ = tmp;
    }
    else {
        depth_ = length_;
        length_ = tmp;
    }
    rotation_ = (rotation_ + NUMBER_OF_ROTATIONS - 1) % NUMBER_OF_ROTATIONS;
}

void Cuboid::mapVertices() {
    x_ = length_ + displacement_[0];
    y_ = height_ + displacement_[1];
    z_ = depth_  + displacement_[2];
    calculateCenter();
}

void Cuboid::setDisplacement(const std::vector<double>& displacement) {
    std::transform(displacement.cbegin(), displacement.cend(), displacement_.begin(), [](double x) -> double {return x;});
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
    mapVertices();
}

Cuboid::Cuboid(Cuboid && other) noexcept
: length_(other.length_)
, height_(other.height_)
, depth_(other.depth_)
, rotation_(other.rotation_)
, displacement_(std::move(other.displacement_))
{
    mapVertices();
}

int Cuboid::getRotation_() const {
    return rotation_;
}

Cuboid &Cuboid::operator=(const Cuboid& other) {
    length_ = other.length_;
    height_ = other.height_;
    depth_ = other.depth_;
    rotation_ = other.rotation_;
    displacement_ = other.displacement_;
    mapVertices();
}

const std::vector<double> Cuboid::getVertices() const{
    return {x_,y_,z_};
}

void Cuboid::rotateHorizontally() {
    (rotation_ % 2 == 0) ? rotate() : rotateBack();
}

std::ostream &operator<<(std::ostream &str, Cuboid &cuboid) {
    cuboid.mapVertices();
    str << cuboid.getLength() << " " << cuboid.getHeight() << " " << cuboid.getDepth() << " ";
    str << cuboid.displacement_[0] << " " << cuboid.displacement_[1] << " " << cuboid.displacement_[2];
}

void Cuboid::checkIfPossible(double length, double depth) {
    if(length < length_ || depth < depth_) {
        if(depth >= length_ && length >= depth_) {
            double tmp = length_;
            length_ = depth_;
            depth_ = tmp;
        }
        else {
            for(int i = 0; i < NUMBER_OF_ROTATIONS; ++i) {
                rotate();
                if((depth >= length_ && length >= depth_) || (depth >= depth_ && length >= length_)) {
                    return;
                }
            }
        }
    }
}

const int Cuboid::getMaxRotations(){
    return NUMBER_OF_ROTATIONS;
}

void Cuboid::calculateCenter() {
    std::get<0>(center) = displacement_[0] + length_/2;
    std::get<1>(center) = displacement_[1] + height_/2;
    std::get<2>(center) = displacement_[2] + depth_ /2;
}

const std::tuple<double, double, double> &Cuboid::getCenter() const {
    return center;
}

double Cuboid::getCoordinate(int coordinate) const {
    switch(coordinate) {
        case 0 : return length_;
        case 1 : return height_;
        case 2 : return depth_;
        default : throw std::out_of_range("Trying to get non-existing coordinate.");
    }
}


