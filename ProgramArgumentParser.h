//
// Created by Kuba on 11.11.2017.
//

#ifndef AAL_PROGRAMARGUMENTPARSER_H
#define AAL_PROGRAMARGUMENTPARSER_H

#include <string>
#include <vector>

class ProgramArgumentParser {
private:
    void showCorrectSyntax();
    void parseFileMode(char* args[]);
    void generateAndSolve(char* args[]);
    void testAndMeasure(char* args[]);
    void showHelpDocument();

public:
    ProgramArgumentParser() = default;
    ~ProgramArgumentParser() = default;
    void parse(int argc, char* argv[]);

};


#endif //AAL_PROGRAMARGUMENTPARSER_H
