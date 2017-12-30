//
// Created by Kuba on 03.11.2017.
//

#ifndef AAL_CUBOIDPARSER_H
#define AAL_CUBOIDPARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include "CuboidContainer.h"

class CuboidParser {
private:

public:
    CuboidParser() = default;
    ~CuboidParser() = default;

    static std::vector<std::vector<CuboidContainer*> > parseFileData();

    static void exportSolutionData(std::vector<CuboidContainer*> data);
};


#endif //AAL_CUBOIDPARSER_H
