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

    int getRotation_() const;

    Cuboid(Cuboid&& other) noexcept;

    ~Cuboid() = default;

    Cuboid& operator=(const Cuboid& other);

    friend std::istream& operator>>(std::istream& str, Cuboid& data);

    friend std::ostream& operator<<(std::ostream &str, Cuboid& data);

    void rotate();

    void rotateBack();

    void rotateHorizontally();

    void mapVertices();

    void setDisplacement(const std::vector<double>& displacement);

    double getLength() const;

    double getHeight() const;

    double getDepth() const;

    const std::vector<double> getVertices() const;
};


#endif //AAL_CUBOID_H
