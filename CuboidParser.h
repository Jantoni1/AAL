//
// Created by Kuba on 03.11.2017.
//

#ifndef AAL_CUBOIDPARSER_H
#define AAL_CUBOIDPARSER_H

#include <fstream>
#include <iostream>
#include "CuboidContainer.h"

class CuboidParser {
private:
    std::ifstream myFile_;
public:
    CuboidParser() = default;
    ~CuboidParser();

    CuboidContainer parseFileData(std::string fileName);
};


#endif //AAL_CUBOIDPARSER_H
