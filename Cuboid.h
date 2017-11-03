//
// Created by Kuba on 03.11.2017.
//

#ifndef AAL_CUBOID_H
#define AAL_CUBOID_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

static int NUMBER_OF_ROTATIONS = 6;

class Cuboid {
private:
    double x_;
    double y_;
    double z_;

    double length_;
    double height_;
    double depth_;

    std::vector<double> displacement_;

    int rotation_;

public:

    Cuboid();

    Cuboid(double length, double height, double depth);

    Cuboid(const Cuboid& other);

    Cuboid(Cuboid&& other) noexcept;

    ~Cuboid() = default;

    friend std::istream& operator>>(std::istream& str, Cuboid& data);

    void rotate();

    void rotate(int rotation);

    void mapVertices();

    void setDisplacement(const std::vector<double>& displacement);

    double getLength() const;

    double getHeight() const;

    double getDepth() const;
};


#endif //AAL_CUBOID_H
