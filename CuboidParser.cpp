//
// Created by Kuba on 03.11.2017.
//

#include "CuboidParser.h"


CuboidParser::~CuboidParser() {
    if(myFile_.is_open()) {
        myFile_.close();
    }
}

CuboidContainer CuboidParser::parseFileData(std::string fileName) {
    CuboidContainer cuboidContainer;
    myFile_.open(fileName);
    myFile_ >> cuboidContainer;
    Cuboid* tmp;
    while(!myFile_.eof()) {
        tmp = new Cuboid();
        myFile_ >> *tmp;
        cuboidContainer.outside_.push_back(tmp);
    }
    myFile_.close();
    return cuboidContainer;
}

