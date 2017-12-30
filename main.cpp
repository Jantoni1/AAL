#include "ProgramArgumentParser.h"

int main(int argc, char* argv[]) {
    ProgramArgumentParser programArgumentParser;
    programArgumentParser.parse(argc, argv);
    return 0;
}