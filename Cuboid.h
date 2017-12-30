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
#include <tuple>


class  Cuboid {
private:
    double x_;
    double y_;
    double z_;

    double length_;
    double height_;
    double depth_;

    std::tuple<double, double, double> center;
    std::vector<double> displacement_;

    int rotation_;
    const static int NUMBER_OF_ROTATIONS = 6;

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

    double getCoordinate(int coordinate) const;

    double getLength() const;

    double getHeight() const;

    double getDepth() const;

    const std::vector<double> getVertices() const;

    void checkIfPossible(double length, double depth);

    static const int getMaxRotations();

    void calculateCenter();

    const std::tuple<double, double, double>& getCenter() const;

};


#endif //AAL_CUBOID_H
