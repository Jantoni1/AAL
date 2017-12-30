//
// Created by Kuba on 02.12.2017.
//

#include "InputValidator.h"

std::vector<int> InputValidator::parseTestModeNumberOfProblemInstances(char *argv[]) const {
    std::vector<std::string> arguments = { "AAL.exe", "-m3","-n", "-k", "-step", "-r"};
    std::vector<int> parsedParameters;
    for(int i = 2; i < 6; ++i) {
        std::string parameter = argv[i];
        if(parameter.size() > arguments[i].size() && parameter.substr(0, arguments[i].size()) == arguments[i]) {
            parsedParameters.push_back(std::stoi(parameter.substr(arguments[i].size(), parameter.size() - arguments[i].size())));
        }
        else {
            throw std::exception();
        }
    }
    return parsedParameters;
}

void InputValidator::showHelpDocument() const {
    std::cout<<"Program can be used in 3 different modes:" << std::endl << std::endl;
    showInteractiveModeHelp();
    showGeneratorModeHelp();
    showTestModeHelp();
}

void InputValidator::showInteractiveModeHelp() const {
    std::cout<<"1) Parse data from stdin file and write output to stdout."<<std::endl;
    std::cout<<"-m1 <[file name1] >[file name2] "<<std::endl;
    std::cout<<"Optional:"<<std::endl;
    std::cout<<"<<[file name1]       input file name"<<std::endl;
    std::cout<<">>[file name2]       output file name"<<std::endl << std::endl;
}
void InputValidator::showGeneratorModeHelp() const {
    std::cout<<"2) Generate data and put it in selected file"<<std::endl;
    std::cout<<"-m2 -n[integer] >[file name]"<< std::endl;
    std::cout<<"-n                  number of problem's instances that will be generated"<<std::endl;
    std::cout<<"Optional:"<<std::endl;
    std::cout<<">>[file name]        output file name"<<std::endl << std::endl;
}

void InputValidator::showTestModeHelp() const {
    std::cout<<"3) Create test cases, solve it and measure time of computing each"<<std::endl;
    std::cout<<"-m3 -n[integer] -k[integer] -step[integer] -r[integer]  " <<std::endl;
    std::cout<<"-n                  initial size"<<std::endl;
    std::cout<<"-k                  number of times problem's n size will be increased"<<std::endl;
    std::cout<<"-step               size increase value for each -k"<<std::endl;
    std::cout<<"-r                  number of instances generated for each problem size"<<std::endl << std::endl;
}

bool InputValidator::checkInputCorrectness(int argc) const {
    if(argc != 2) {
        std::cout<<" Solver mode syntax: " << std::endl;
        showInteractiveModeHelp();
        return false;
    }
    return true;
}


int InputValidator::parseGeneratorModeNumberOfProblemInstances(char **argv) const {
    std::string str = argv[2];
    int numberOfProblems;
    if(str.substr(0, 2) == "-n") {
        numberOfProblems = std::stoi(str.substr(2, str.size() - 2));
    }
    else throw std::exception();
    return numberOfProblems;
}

void InputValidator::showCorrectSyntax() const {
    std::cout<<"Use: AAL.exe [-mode] [arguments]"<< std::endl;
    std::cout<<"For more info run program with -help flag"<<std::endl;
}

