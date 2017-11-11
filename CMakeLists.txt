cmake_minimum_required(VERSION 3.8)
project(AAL)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Cuboid.cpp Cuboid.h Solver.cpp Solver.h CuboidContainer.cpp CuboidContainer.h NaiveSolver.cpp NaiveSolver.h CuboidParser.cpp CuboidParser.h ShelfSolver.cpp ShelfSolver.h Shelf.cpp Shelf.h TreeShelfSolver.cpp TreeShelfSolver.h TreeShelf.cpp TreeShelf.h ProgramArgumentParser.cpp ProgramArgumentParser.h)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable (AAL ${SOURCE_FILES})

