//
// Created by Kuba on 11.11.2017.
//

#ifndef AAL_PROGRAMARGUMENTPARSER_H
#define AAL_PROGRAMARGUMENTPARSER_H

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <random>
#include <chrono>
#include <functional>
#include <memory>
#include "CuboidContainer.h"
#include "CuboidParser.h"
#include "NaiveSolver.h"
#include "ShelfSolver.h"
#include "TreeShelfSolver.h"
#include "InputValidator.h"

class ProgramArgumentParser {
private:
    std::random_device rd_;

    std::mt19937 gen_;

    std::uniform_real_distribution<double> unif_;

    std::uniform_int_distribution<int> unifInt_;

    int min_;

    int max_;

    InputValidator inputValidator;

    std::vector<std::pair<std::string, std::function<void(int, char**)> > > programModes_;


    void parseFileMode(int argc, char* argv[]) const;

    void generateAndSolve(int argc, char* argv[]);

    void testAndMeasure(int argc, char* argv[]);

    void runNaiveSolver(CuboidContainer& cuboidContainer) const;

    void runShelfSolver(CuboidContainer& cuboidContainer) const;

    void runTreeShelfSolver(CuboidContainer& cuboidContainer) const;

    void runBruteForceSolver(CuboidContainer& cuboidContainer) const;

    void runSolvers() const;

    std::vector<std::vector<CuboidContainer*> >createCuboidContainers() const;

    void runAlgorithms(std::vector<CuboidContainer*>& containers) const;

    void generateSolveAndExportProblemInstances(int numberOfInstances);

    std::vector<long long int> generateSolveAndExportProblemInstances(int numberOfInstances, int problemSize);

    CuboidContainer* generateSingleProblem();

    CuboidContainer* generateSingleProblem(int numberOfCuboids);

    double generateRandomDouble();

    int generateRandomInt();

    long long int measureAlgorithmTime(std::function<void(CuboidContainer &cuboidContainer)> function, CuboidContainer &cuboidContainer) const;

    void createStatistics(std::vector<int>& parameters);
public:
    ProgramArgumentParser();

    ~ProgramArgumentParser() = default;

    void parse(int argc, char* argv[]);

};


#endif //AAL_PROGRAMARGUMENTPARSER_H
