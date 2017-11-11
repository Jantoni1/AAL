//
// Created by Kuba on 03.11.2017.
//

#ifndef AAL_CUBOIDARRAY_H
#define AAL_CUBOIDARRAY_H


#include "Cuboid.h"

class CuboidContainer {
private:
    std::vector<Cuboid*> emplaced_;

    double length_;
    double height_;
    double depth_;

public:
    std::vector<Cuboid*> outside_;

    CuboidContainer();
    CuboidContainer(const CuboidContainer& other);
    CuboidContainer(double length, double depth);

    ~CuboidContainer();

    double getLength() const;

    double getHeight() const;

    double getDepth() const;

    void put(Cuboid* cuboid);
    const std::vector<Cuboid*> &getEmplaced_() const;

    friend std::istream& operator>>(std::istream& str, CuboidContainer& data);

    friend std::ostream& operator<<(std::ostream& str, CuboidContainer& data);

    void setHeight(double height);
};


#endif //AAL_CUBOIDARRAY_H
