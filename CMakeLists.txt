cmake_minimum_required(VERSION 3.8)
project(AAL)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Cuboid.cpp Cuboid.h Solver.cpp Solver.h CuboidContainer.cpp CuboidContainer.h NaiveSolver.cpp NaiveSolver.h CuboidParser.cpp CuboidParser.h)

add_executable (AAL ${SOURCE_FILES})