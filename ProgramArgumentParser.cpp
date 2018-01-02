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
}

void ProgramArgumentParser::parseFileMode(int argc, char* argv[]) const {
//    std::vector<std::string> fileNames = inputValidator.parseInteractiveModeArguments(argc, argv);
    std::vector<int> arguments;
    try {
        arguments = inputValidator.checkInputCorrectness(argc, argv);
    }
    catch(std::exception& e) {
        inputValidator.showCorrectSyntax();
    }
    runSolvers(arguments[0]);
}

void ProgramArgumentParser::generateAndSolve(int argc, char* argv[]) {
    if(argc != 3) {
        inputValidator.showCorrectSyntax();
        return;
    }
    int numberOfCuboids;
    try {
        numberOfCuboids = inputValidator.parseGeneratorModeNumberOfProblemInstances(argv);
    }
    catch(std::exception& exception) {
        inputValidator.showCorrectSyntax();
        return;
    }
    generateSolveAndExportProblemInstances(numberOfCuboids);
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

void ProgramArgumentParser::runSolvers(int algorithm) const {
    std::vector<CuboidContainer*> containers = createCuboidContainers();
    for(int i = 0; i < 3; ++i) {
        if(algorithm == 3 || algorithm == i) {
            runAlgorithms(i, containers[i]);
        }
        else {
            auto* cuboid = new Cuboid(0.0, 0.0, 0.0);
            containers[i]->put(cuboid);
        }
        if(i == 0) {
            CuboidContainer* container = containers[0];
            std::cout<<*container;
        }
        else {
            std::cout<<std::endl;
            for(auto cuboid : containers[i]->getEmplaced()) {
                std::cout<<std::endl<<*cuboid;
            }
        }
    }
    for(auto* container : containers) {
         delete container;
     }
}

std::vector<CuboidContainer*> ProgramArgumentParser::createCuboidContainers() const {
    std::vector<std::vector<CuboidContainer* > > problemInstances = CuboidParser::parseFileData();
    for(auto& vec : problemInstances) {
        vec.push_back(new CuboidContainer(*vec.front()));
        vec.push_back(new CuboidContainer(*vec.front()));
    }
    return problemInstances.front();
}

void ProgramArgumentParser::runAlgorithms(int algorithm, CuboidContainer* container) const {
    algorithms[algorithm](*container);
}

void ProgramArgumentParser::generateSolveAndExportProblemInstances(int numberOfCuboids) {
    CuboidContainer* problemInstance = generateSingleProblem(numberOfCuboids);
    std::cout<<problemInstance->getLength()<<" "<<problemInstance->getDepth();
    for(auto* cuboid : problemInstance->outside_) {
        std::cout<<std::endl<<cuboid->getLength()<<" "<<cuboid->getHeight()<<" "<<cuboid->getDepth();
    }
    delete problemInstance;
}

long long int ProgramArgumentParser::generateSolveAndExportProblemInstances(int algorithm, int numberOfInstances, int problemSize) {
    std::vector<CuboidContainer *> problemInstances;
    for(int i = 0; i < numberOfInstances; ++i) {
        problemInstances.push_back(generateSingleProblem(problemSize));
    }
    long long int times = 0;
    std::vector<std::function<void(CuboidContainer&)> > algorithms = {
            std::bind(&ProgramArgumentParser::runNaiveSolver, this, std::placeholders::_1),
            std::bind(&ProgramArgumentParser::runShelfSolver, this, std::placeholders::_1),
            std::bind(&ProgramArgumentParser::runBruteForceSolver, this, std::placeholders::_1)
    };
    for(auto* cuboidContainer : problemInstances) {
        for(int i = 0; i < 3; ++i) {
            times += measureAlgorithmTime(algorithms[algorithm], *cuboidContainer) / numberOfInstances;
        }
    }
    for(auto* cuboidContainer : problemInstances) {
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
    double x = cuboidContainer->getDepth(), y = cuboidContainer->getHeight(), z = cuboidContainer->getDepth();
    double seed = std::min(x, std::min(y, z));
    for(int i = 0; i < numberOfCuboids; ++i) {
        cuboidContainer->outside_.push_back(new Cuboid(generateRandomDouble(cuboidContainer->getLength())
                , generateRandomDouble(std::max(cuboidContainer->getLength(), cuboidContainer->getDepth())),
                                                       generateRandomDouble(cuboidContainer->getDepth())));
    }
    return cuboidContainer;
}

double ProgramArgumentParser::generateRandomDouble() {
    return unif_(gen_);
}

double ProgramArgumentParser::generateRandomDouble(double seed) {
    return seed*fractions_(gen_);
}

ProgramArgumentParser::ProgramArgumentParser()
{
    gen_ = std::mt19937(rd_());
    min_ = 1;
    max_ = 20;
    double lower_bound = 0;
    double upper_bound = 1000;
    unif_ =  std::uniform_real_distribution<double>(lower_bound,upper_bound);
    fractions_ = std::uniform_real_distribution<double>(0.1, 0.25);
    unifInt_ = std::uniform_int_distribution<>(min_, max_);
    programModes_.emplace_back(std::make_pair("-m1", [&](int argc, char** argv) {parseFileMode(argc, argv);}));
    programModes_.emplace_back(std::make_pair("-m2", [&](int argc, char** argv) {generateAndSolve(argc, argv);}));
    programModes_.emplace_back(std::make_pair("-m3", [&](int argc, char** argv) {testAndMeasure(argc, argv);}));
    programModes_.emplace_back(std::make_pair("-help", [&](int argc, char** argv) {inputValidator.showHelpDocument();}));

    functions.emplace_back([](double value) -> double {return value;});
    functions.emplace_back([](double value) -> double {return value;});
    functions.emplace_back([&](double value) -> double {return bruteForceComplexity(value);});

    algorithms.emplace_back([&](CuboidContainer& cuboidContainer){return runNaiveSolver(cuboidContainer);});
    algorithms.emplace_back([&](CuboidContainer& cuboidContainer){return runShelfSolver(cuboidContainer);});
    algorithms.emplace_back([&](CuboidContainer& cuboidContainer){return runBruteForceSolver(cuboidContainer);});
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
    int algorithm = parameters[0];
    int n = parameters[1];
    int step = parameters[3];
    int numberOfInstances = parameters[4];

    std::vector<std::tuple<int, long long int, double> >  times;
    for(int i = 0;i < parameters[2]; i++, n += step ) {
        long long int measuredTimes = generateSolveAndExportProblemInstances(algorithm, numberOfInstances, n);
        times.emplace_back(n, measuredTimes, 0.0);
    }
    int size = times.size();
    bool medianType = size % 2 == 1;
    long long int medianTime = medianType
                 ? std::get<1>(times[size / 2])
                 : (std::get<1>(times[size / 2 ]) + std::get<1>(times[size/2 - 1])) / 2;
    int median = medianType
                 ? std::get<0>(times[size / 2])
                 : (std::get<0>(times[size / 2 ]) + std::get<0>(times[size/2 - 1])) / 2;
    int medianComplexity = median;
    for(auto& tuple : times) {
        std::get<2>(tuple) = timeComplexityCalculator(algorithm, std::get<1>(tuple), std::get<0>(tuple), medianComplexity, medianTime);
    }
    for(const auto& pair : times) {
        std::cout<< std::get<0>(pair) << "      " << std::get<1>(pair)<< "      " << std::get<2>(pair)<< std::endl;
    }
}

void ProgramArgumentParser::runBruteForceSolver(CuboidContainer &cuboidContainer) const {
    BruteForceSolver bruteForceSolver;
    bruteForceSolver.arrange(cuboidContainer);
}

double ProgramArgumentParser::factorial(double number) const {
    if(number == 0) {
        return 1;
    }
    if(number < 0) {
        throw std::logic_error("Trying to calculate factorial of negative integer");
    }
    int factorial= 1;
    for(int i = 1; i < number; ++i) {
        factorial *= i;
    }
    return factorial;
}

double ProgramArgumentParser::timeComplexityCalculator(int mode, double time, double complexity, double medianComplexity, double medianTime) const {
    return (time * functions[mode](medianComplexity) ) / (functions[mode](complexity) * medianTime);
}

double ProgramArgumentParser::bruteForceComplexity(double n) {
    double product = 1;
    for(int i = 0; i < n; ++i) {
        product *= 12;
    }
    return product * factorial(n) * factorial(n+1) * (n-1);
}


