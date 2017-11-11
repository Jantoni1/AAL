//
// Created by Kuba on 11.11.2017.
//

#include <iostream>
#include "ProgramArgumentParser.h"

void ProgramArgumentParser::parse(int argc, char* argv[]) {
    std::string command = argv[1];
    if(command.compare("-m1") == 0) {
        parseFileMode(argv);
    } else if (command.compare("-m2") == 0) {
        generateAndSolve(argv);
    } else if(command.compare("-m3") == 0) {
        testAndMeasure(argv);
    } else if(command.compare("-help") == 0) {
        showHelpDocument();
    } else {
        showCorrectSyntax();
    }
}

void ProgramArgumentParser::showCorrectSyntax() {
    std::cout<<"Use: AAL.exe [-mode] [arguments]"<< std::endl;
    std::cout<<"For more info run program with -help flag"<<std::endl;
}

void ProgramArgumentParser::parseFileMode(char **args) {

}

void ProgramArgumentParser::generateAndSolve(char **args) {

}

void ProgramArgumentParser::testAndMeasure(char **args) {

}

void ProgramArgumentParser::showHelpDocument() {
    std::cout<<"Program can be used in 3 different modes" << std::endl;
    std::cout<<"1) Parse data from given file and write output to selected file."<<std::endl;
    std::cout<<"-m1 <<[input file name] >>[output file name] "<<std::endl;
    std::cout<<"2) Generate data, solve problems and put information in selected file"<<std::endl;
    std::cout<<"-m2 n[number of problem's instances] >>[output file name]"<< std::endl;
    std::cout<<"3) Create test cases, solve it and measure time of computing each"<<std::endl;
}
