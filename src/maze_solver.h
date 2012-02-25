/*! \file maze_solver.h
 *  \author Soo-Hyun Yoo
 *  \brief Maze solver bot.
 */

#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "globals.h"
#include "motors.h"
#include "movements.cpp"

class MazeSolver {
    // Controllers
    void mazeSolver();
    void lightFollower();
    void wallFollower();

public:
    MazeSolver();
    void run();
};

#endif // MAZE_SOLVER_H

