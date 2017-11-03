#include "main.h"
#include "CuboidParser.h"
#include "NaiveSolver.h"

int main(int argc, char* argv[]) {
    if(argc > 1) {
        CuboidParser cuboidParser;
        std::cout<<argv[1]<<std::endl;
        CuboidContainer cuboidContainer = cuboidParser.parseFileData(argv[1]);
        NaiveSolver solver;
        solver.arrange(cuboidContainer);
        std::cout<<"Wysokosc prostopadloscianu obliczona algorytmem naiwnym wynosi: "<<cuboidContainer.getHeight()<<std::endl;
    }
}