//
// Created by Kuba on 26.12.2017.
//

#include "CornerContainer.h"

CornerContainer::Corner::Corner(double x, double y, double z, CornerContainer::Position position, Corner* parent)
        :   x_(x)
        ,   y_(y)
        ,   z_(z)
        ,   position_(position)
        ,   parent_(parent)
        ,   cuboid(nullptr)
{}

CornerContainer::Corner::~Corner() {
    clear();
}

void CornerContainer::Corner::clear() {
    for(auto* corner : children) {
        delete corner;
    }
    children.clear();
    cuboid = nullptr;
}

bool CornerContainer::Corner::isEmpty() {
    return cuboid == nullptr;
}

void CornerContainer::Corner::addCuboid(Cuboid *cuboid) {
    this->cuboid = cuboid;
    for(int i = 0; i < 3; ++i) {
        children.push_back(new Corner(x_, y_, z_, position_, this));
    }
    if(position_ == FRONT_LEFT || position_ == BACK_LEFT) {
        children[0]->x_ += cuboid->getLength();
    }
    else {
        children[0]->x_ -= cuboid->getLength();
    }
    if(position_ == FRONT_LEFT || position_ == FRONT_RIGHT) {
        children[2]->z_ += cuboid->getDepth();
    }
    else {
        children[2]->z_ -= cuboid->getDepth();
    }
    children[1]->y_ += cuboid->getHeight();
    cuboid->mapVertices();
}

double CornerContainer::Corner::getCoordinate(int coordinate) {
    switch(coordinate) {
        case 0 : return x_;
        case 1 : return y_;
        case 2 : return z_;
        default : throw std::out_of_range("Trying to get non-existing coordinate.");
    }
}

void CornerContainer::createCorners(const CuboidContainer &container) {
    corners.push_back(new Corner(0.0, 0.0, 0.0, Position::FRONT_LEFT, nullptr));
    corners.push_back(new Corner(container.getLength(), 0.0, 0.0, Position::FRONT_RIGHT, nullptr));
    corners.push_back(new Corner(0.0, 0.0, container.getDepth(), Position::BACK_LEFT, nullptr));
    corners.push_back(new Corner(container.getLength(), 0, container.getDepth(), Position::BACK_RIGHT, nullptr));
}

CornerContainer::~CornerContainer() {
    clear();
}

void CornerContainer::clear() {
    for(auto* corner : corners) {
        delete corner;
    }
    corners.clear();
}

CornerContainer::Iterator CornerContainer::begin() {
    if(corners.empty()) {
        return CornerContainer::Iterator(*this, nullptr);
    }
    std::vector<int> stack;
    Corner* corner = corners.front();
    stack.push_back(0);
    while(!corner->children.empty()) {
        corner = corner->children.front();
        stack.push_back(0);
    }
    return CornerContainer::Iterator(*this, corner, stack);
}

CornerContainer::Iterator CornerContainer::end() {
    return CornerContainer::Iterator(*this, nullptr);
}

CornerContainer::Iterator::Iterator(CornerContainer &parent, CornerContainer::Corner *current)
        : parent_(parent)
        , current_(current)
{}

CornerContainer::Iterator::Iterator(CornerContainer &parent, CornerContainer::Corner *current,
                                    const std::vector<int> &stack)
: Iterator(parent, current)
{
    for(auto x : stack) {
        stack_.push_back(x);
    }
}

bool CornerContainer::Iterator::operator==(const CornerContainer::Iterator &other) {
    return (&parent_ == &other.parent_ && current_ == other.current_);
}

bool CornerContainer::Iterator::operator!=(const CornerContainer::Iterator &other) {
    return (&parent_ != &other.parent_ || current_ != other.current_);
}

CornerContainer::Iterator &CornerContainer::Iterator::operator++() {
    if(stack_.empty()) {
        throw std::out_of_range("Tried to increment end() iterator");
    }
    if((stack_.back() == 2 && stack_.size() > 1) || (stack_.back() == parent_.corners.size() - 1)) {
        stack_.pop_back();
        current_ = current_->parent_;
        return *this;
    }
    //go to the next child of current's parent
    std::vector<Corner*> corners = stack_.size() == 1 ? parent_.corners :  current_->parent_->children;
    current_ = corners[++stack_.back()];
    while(!current_->children.empty()) {
        current_ = current_->children.front();
        stack_.push_back(0);
    }
    return *this;
}

CornerContainer::Iterator CornerContainer::Iterator::operator++(int) {
    CornerContainer::Iterator copy = *this;
    ++(*this);
    return copy;
}

CornerContainer::Corner *CornerContainer::Iterator::operator->() {
    return current_;
}

CornerContainer::Corner *CornerContainer::Iterator::operator*() {
    return current_;
}





