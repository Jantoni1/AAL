//
// Created by Kuba on 03.11.2017.
//

#include "CuboidParser.h"



std::vector<std::vector<CuboidContainer*> > CuboidParser::parseFileData() {
    std::stringstream stringStream;
    std::string line;
    std::vector<std::vector<CuboidContainer*> > problemInstances;
    CuboidContainer* container;
    problemInstances.emplace_back(std::vector<CuboidContainer*>());
    problemInstances.back().push_back(new CuboidContainer());
    std::getline(std::cin, line);
    if(line.empty()) {
        delete problemInstances.back().back();
        throw std::logic_error("File formatting problem");
    }
    stringStream << line;
    container = problemInstances.back().back();
    stringStream >> *container;
    stringStream.clear();
    Cuboid* tmp;
    while(!std::cin.eof()) {
        std::getline(std::cin, line);
        if(line.empty()) {
            problemInstances.emplace_back(std::vector<CuboidContainer*>());
            problemInstances.back().push_back(new CuboidContainer());
            if(!std::cin.eof()) {
                std::getline(std::cin, line);
                if(line.empty()) {
                    for(auto& vec : problemInstances) {
                        for(auto* element : vec) {
                            delete element;
                        }
                    }
                    throw std::logic_error("File formatting problem");
                }
                stringStream << line;
                container = problemInstances.back().back();
                stringStream >> *container;
                stringStream.clear();
                continue;
            }
            else return problemInstances;
        }
        stringStream << line;
        tmp = new Cuboid();
        stringStream >> *tmp;
        problemInstances.back().back()->outside_.push_back(tmp);
        stringStream.clear();
    }
    return problemInstances;
}



void CuboidParser::exportSolutionData(std::vector<CuboidContainer*> data) {
    for(CuboidContainer* cuboidContainer : data) {
        std::cout << *cuboidContainer <<std::endl;
    }
}


