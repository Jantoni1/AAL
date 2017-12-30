//
// Created by Kuba on 11.11.2017.
//

#include "ProgramArgumentParser.h"
#include "BruteForceSolver.h"


void ProgramArgumentParser::parse(int argc, char* argv[]) {
    if(argc <= 1 ) {
        inputValidator.showCorrectSyntax();
        return;
    }
    std::string command = argv[1];
    for(auto& pair : programModes_) {
        if(command == pair.first) {
            pair.second(argc, argv);
            return;
        }
    }
    inputValidator.showCorrectSyntax();
} //TODO parsowanie kilku problemow naraz trzeba obadac, zepsuty m2, algorytmy jakkolwiek tbh; OpenGL

void ProgramArgumentParser::parseFileMode(int argc, char* argv[]) const {
//    std::vector<std::string> fileNames = inputValidator.parseInteractiveModeArguments(argc, argv);
    if(!inputValidator.checkInputCorrectness(argc)) {
        return;
   }
    runSolvers();
}

void ProgramArgumentParser::generateAndSolve(int argc, char* argv[]) {
    if(argc != 3) {
        inputValidator.showCorrectSyntax();
        return;
    }
    int numberOfProblemInstances;
    try {
        numberOfProblemInstances = inputValidator.parseGeneratorModeNumberOfProblemInstances(argv);
    }
    catch(std::exception& exception) {
        inputValidator.showCorrectSyntax();
        return;
    }
    generateSolveAndExportProblemInstances(numberOfProblemInstances);
}

void ProgramArgumentParser::testAndMeasure(int argc, char* argv[]) {
    if(argc < 5) {
        inputValidator.showCorrectSyntax();
        return;
    }
    try {
        std::vector<int> parameters = inputValidator.parseTestModeNumberOfProblemInstances(argv);
        std::string fileName;
        createStatistics(parameters);
    }
    catch(std::exception& exception) {
        inputValidator.showCorrectSyntax();
        return;
    }
}

void ProgramArgumentParser::runNaiveSolver(CuboidContainer &cuboidContainer) const {
    NaiveSolver solver;
    solver.arrange(cuboidContainer);
}

void ProgramArgumentParser::runShelfSolver(CuboidContainer &cuboidContainer) const {
    ShelfSolver shelfSolver;
    shelfSolver.arrange(cuboidContainer);
}

// NOT USED
void ProgramArgumentParser::runTreeShelfSolver(CuboidContainer &cuboidContainer) const {
    TreeShelfSolver treeShelfSolver;
    treeShelfSolver.arrange(cuboidContainer);
}

void ProgramArgumentParser::runSolvers() const {
    std::vector<std::vector<CuboidContainer*> > containers = createCuboidContainers();
    for(auto& vec : containers) {
        runAlgorithms(vec);
        CuboidParser::exportSolutionData(vec);
    }
    for(auto& vec : containers) {
        for(auto* cuboid : vec) {
            delete cuboid;
        }
    }
}

std::vector<std::vector<CuboidContainer*> > ProgramArgumentParser::createCuboidContainers() const {
    std::vector<std::vector<CuboidContainer* > > problemInstances = CuboidParser::parseFileData();
    for(auto& vec : problemInstances) {
        vec.push_back(new CuboidContainer(*vec.back()));
        vec.push_back(new CuboidContainer(*vec.back()));
    }
    return problemInstances;
}

void ProgramArgumentParser::runAlgorithms(std::vector<CuboidContainer *> &containers) const {
    runNaiveSolver(*containers[0]);
    runShelfSolver(*containers[1]);
    runBruteForceSolver(*containers[2]);
}

void ProgramArgumentParser::generateSolveAndExportProblemInstances(int numberOfInstances) {
    std::vector<CuboidContainer *>  problemInstances;
    for(int i = 0; i < numberOfInstances; ++i) {
        problemInstances.push_back(generateSingleProblem());
        std::cout<<problemInstances[i]->getLength()<<" "<<problemInstances[i]->getDepth();
        for(auto* cuboid : problemInstances[i]->outside_) {
            std::cout<<std::endl<<cuboid->getLength()<<" "<<cuboid->getHeight()<<" "<<cuboid->getDepth();
        }
    }

    for(auto* cuboidContainer : problemInstances) {
        delete cuboidContainer;
    }
}

std::vector<long long int> ProgramArgumentParser::generateSolveAndExportProblemInstances(int numberOfInstances, int problemSize) {
    std::vector<std::vector<CuboidContainer *> > problemInstances;
    for(int i = 0; i < numberOfInstances; ++i) {
        problemInstances.emplace_back(std::vector<CuboidContainer*>());
        problemInstances.back().push_back(generateSingleProblem(problemSize));
        problemInstances.back().push_back(new CuboidContainer(*problemInstances.back().back()));
        problemInstances.back().push_back(new CuboidContainer(*problemInstances.back().back()));
    }

    std::vector<long long int> times = {0, 0, 0};
    std::vector<std::function<void(CuboidContainer&)> > algorithms = {
            std::bind(&ProgramArgumentParser::runNaiveSolver, this, std::placeholders::_1),
            std::bind(&ProgramArgumentParser::runShelfSolver, this, std::placeholders::_1),
            std::bind(&ProgramArgumentParser::runBruteForceSolver, this, std::placeholders::_1)
    };
    for(std::vector<CuboidContainer *>& vector : problemInstances) {
        for(int i = 0; i < 3; ++i) {
            times[i] += measureAlgorithmTime(algorithms[i], *vector[i]) / numberOfInstances;
        }
    }

    std::vector<CuboidContainer*> allProblems;
    for(auto& vec : problemInstances) {
        for(auto* element : vec) {
            allProblems.push_back(element);
        }
    }

    //CuboidParser::exportSolutionData(fileName, allProblems);
    for(auto* cuboidContainer : allProblems) {
        delete cuboidContainer;
    }

    return times;
}

CuboidContainer *ProgramArgumentParser::generateSingleProblem() {
    auto* cuboidContainer = new CuboidContainer(generateRandomDouble(), generateRandomDouble());
    int numberOfCuboids = generateRandomInt();
    for(int i = 0; i < numberOfCuboids; ++i) {
        cuboidContainer->outside_.push_back(new Cuboid(std::min(generateRandomDouble(), cuboidContainer->getLength())
                , generateRandomDouble(), std::min(generateRandomDouble(),cuboidContainer->getDepth())));
    }
    return cuboidContainer;
}

CuboidContainer *ProgramArgumentParser::generateSingleProblem(int numberOfCuboids) {
    auto* cuboidContainer = new CuboidContainer(generateRandomDouble(), generateRandomDouble());
    for(int i = 0; i < numberOfCuboids; ++i) {
        cuboidContainer->outside_.push_back(new Cuboid(std::min(generateRandomDouble(), cuboidContainer->getLength())
                , generateRandomDouble(), std::min(generateRandomDouble(),cuboidContainer->getDepth())));
    }
    return cuboidContainer;
}

double ProgramArgumentParser::generateRandomDouble() {
    return unif_(gen_);
}

ProgramArgumentParser::ProgramArgumentParser()
{
    gen_ = std::mt19937(rd_());
    min_ = 1;
    max_ = 20;
    double lower_bound = 0;
    double upper_bound = 1000;
    unif_ =  std::uniform_real_distribution<double>(lower_bound,upper_bound);
    unifInt_ = std::uniform_int_distribution<>(min_, max_);
    programModes_.emplace_back(std::make_pair("-m1", [&](int argc, char** argv) {parseFileMode(argc, argv);}));
    programModes_.emplace_back(std::make_pair("-m2", [&](int argc, char** argv) {generateAndSolve(argc, argv);}));
    programModes_.emplace_back(std::make_pair("-m3", [&](int argc, char** argv) {testAndMeasure(argc, argv);}));
    programModes_.emplace_back(std::make_pair("-help", [&](int argc, char** argv) {inputValidator.showHelpDocument();}));
}

int ProgramArgumentParser::generateRandomInt() {
    return unifInt_(gen_);
}

long long int ProgramArgumentParser::measureAlgorithmTime(std::function<void(CuboidContainer&)> function, CuboidContainer &cuboidContainer) const {
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    function(cuboidContainer);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
}

void ProgramArgumentParser::createStatistics(std::vector<int>& parameters) {
    int n = parameters[0];
    int step = parameters[2];
    int numberOfInstances = parameters[3];
    std::vector<std::vector<std::tuple<int, long long int, double> > > times = { std::vector<std::tuple<int, long long int, double> >(),
                                                                        std::vector<std::tuple<int, long long int, double> >(),
                                                                        std::vector<std::tuple<int, long long int, double> >()
                                                                        };
    for(int i = 0;i < parameters[1]; i++, n += step ) {
        std::vector<long long int> measuredTimes = generateSolveAndExportProblemInstances(numberOfInstances, n);
        for(int k = 0; k < 3; ++k) {
            times[k].emplace_back(n, measuredTimes[k], 0.0);
        }
    }
    for(int i = 0; i < 3; ++i) {
        int size = times[i].size();
        bool medianType = size % 2 == 1;
        long long int medianTime = medianType
                     ? std::get<1>(times[i][size / 2])
                     : (std::get<1>(times[i][size / 2 ]) + std::get<1>(times[i][size/2 - 1])) / 2;
        int median = medianType
                     ? std::get<0>(times[i][size / 2])
                     : (std::get<0>(times[i][size / 2 ]) + std::get<0>(times[i][size/2 - 1])) / 2;
        int medianComplexity = median;
        for(auto& tuple : times[i]) {
            std::cout<<std::get<0>(tuple) << " " << medianComplexity << " " << std::get<1>(tuple) << " " << medianTime << std::endl;
            std::get<2>(tuple) = ( static_cast<double>(std::get<1>(tuple)) * static_cast<double>(medianComplexity * medianComplexity)
                                   / (static_cast<double>(std::get<0>(tuple) * std::get<0>(tuple)) * static_cast<double>(medianTime)));
            std::cout << std::get<2>(tuple) << std::endl;
        }
    }
    for(int k = 0; k < 3; ++k) {
        for(const auto& pair : times[k]) {
            std::cout<< std::get<0>(pair) << "      " << std::get<1>(pair)<< "      " << std::get<2>(pair)<< std::endl;
        }
    }
}

void ProgramArgumentParser::runBruteForceSolver(CuboidContainer &cuboidContainer) const {
    BruteForceSolver bruteForceSolver;
    bruteForceSolver.arrange(cuboidContainer);
}


