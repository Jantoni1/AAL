#include "CuboidParser.h"
#include "NaiveSolver.h"
#include "ShelfSolver.h"
#include "TreeShelfSolver.h"
#include "ProgramArgumentParser.h"

int main(int argc, char* argv[]) {

    if(argc > 1) {
        ProgramArgumentParser programArgumentParser;
        programArgumentParser.parse(argc, argv);
        return 0;

        CuboidParser cuboidParser;
        CuboidContainer cuboidContainer = cuboidParser.parseFileData(argv[1]);
        NaiveSolver solver;
        solver.arrange(cuboidContainer);
        std::cout<<"Wysokosc prostopadloscianu obliczona algorytmem naiwnym wynosi: "<<cuboidContainer.getHeight()<<std::endl;
        ShelfSolver shelfSolver;
        CuboidContainer cuboidContainer1 = cuboidParser.parseFileData(argv[1]);
        shelfSolver.arrange(cuboidContainer1);
        std::cout<<"Wysokosc prostopadloscianu obliczona algorytmem polkowym wynosi: "<<cuboidContainer1.getHeight()<<std::endl;
        CuboidContainer cuboidContainer2 = cuboidParser.parseFileData(argv[1]);
        TreeShelfSolver treeShelfSolver;
        treeShelfSolver.arrange(cuboidContainer2);
        std::cout<<"Wysokosc prostopadloscianu obliczona algorytmem polkowym drzewiastym wynosi: "<<cuboidContainer2.getHeight()<<std::endl;
    }
}