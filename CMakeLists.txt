cmake_minimum_required(VERSION 3.8)
project(AAL)

set(CMAKE_CXX_STANDARD 17)

#add_definitions(-DBOOST_ALL_NO_LIB)
#set(BOOST_ROOT "D:/Boost/boost_1_60_0")
#set(Boost_INCLUDE_DIR "D:/Boost/boost_1_60_0/include")
#set(Boost_LIBRARY_DIR "D:/Boost/boost_1_60_0/lib")
#
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.60.0 COMPONENTS test)
#include_directories(${Boost_INCLUDE_DIRS} )


set(SOURCE_FILES main.cpp Cuboid.cpp Cuboid.h Solver.cpp Solver.h CuboidContainer.cpp CuboidContainer.h NaiveSolver.cpp NaiveSolver.h CuboidParser.cpp CuboidParser.h ShelfSolver.cpp ShelfSolver.h Shelf.cpp Shelf.h TreeShelfSolver.cpp TreeShelfSolver.h TreeShelf.cpp TreeShelf.h ProgramArgumentParser.cpp ProgramArgumentParser.h InputValidator.cpp InputValidator.h BruteForceSolver.cpp BruteForceSolver.h CornerContainer.cpp CornerContainer.h)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable (AAL ${SOURCE_FILES})

