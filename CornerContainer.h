//
// Created by Kuba on 26.12.2017.
//

#ifndef AAL_CORNERCONTAINER_H
#define AAL_CORNERCONTAINER_H

#include "Cuboid.h"
#include "CuboidContainer.h"
#include <vector>

class CornerContainer {
public:
    struct Corner;
    class Iterator;

    enum Position{FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT};

    CornerContainer() = default;
    ~CornerContainer();
    void createCorners(const CuboidContainer& container);
    void clear();
    Iterator begin();
    Iterator end();

private:

    std::vector<Corner*> corners;

};

struct CornerContainer::Corner {
    Corner(double x, double y, double z, Position position, Corner* parent);
    ~Corner();
    void clear();
    bool isEmpty();
    void addCuboid(Cuboid* cuboid);
    double getCoordinate(int coordinate);
    double x_;
    double y_;
    double z_;
    Position position_;
    Cuboid* cuboid;
    std::vector<Corner*> children;
    Corner* parent_;
};

class CornerContainer::Iterator {
private:
    CornerContainer& parent_;
    Corner* current_;
    std::vector<int> stack_;

public:
    Iterator(CornerContainer& parent, Corner* current);
    Iterator(CornerContainer& parent, Corner* current, const std::vector<int>& stack);
    Iterator(const Iterator& other) = default;
    ~Iterator() = default;
    bool operator==(const Iterator& other);
    bool operator!=(const Iterator& other);
    Iterator& operator++();
    Iterator operator++(int);
    CornerContainer::Corner* operator->();
    CornerContainer::Corner* operator*();
};

#endif //AAL_CORNERCONTAINER_H
