//
// Created by Kuba on 02.12.2017.
//

#ifndef AAL_INPUTVALIDATOR_H
#define AAL_INPUTVALIDATOR_H
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>

class InputValidator {
public:
    InputValidator() = default;

    ~InputValidator() = default;

    std::vector<int> parseTestModeNumberOfProblemInstances(char *argv[]) const;

    void showHelpDocument() const;

    std::vector<int> checkInputCorrectness(int argc, char** argv) const;

    int parseGeneratorModeNumberOfProblemInstances(char* argv[]) const;

    void showCorrectSyntax() const;

private:

    void showInteractiveModeHelp() const;

    void showGeneratorModeHelp() const;

    void showTestModeHelp() const;
};


#endif //AAL_INPUTVALIDATOR_H
