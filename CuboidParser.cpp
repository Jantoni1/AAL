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
    std::vector<Cuboid> outside;
    myFile_.open(fileName);
    myFile_ >> cuboidContainer;
    while(!myFile_.eof()) {
        cuboidContainer.outside_.emplace_back(*(new Cuboid()));
        myFile_ >> cuboidContainer.outside_.back();
    }
    myFile_.close();
    return cuboidContainer;
}

