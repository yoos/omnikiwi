/*! \file maze_solver.h
 *  \author Soo-Hyun Yoo
 *  \brief Maze solver bot.
 */

#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "globals.h"
#include "motors.h"

class MazeSolver {
    uint64_t unitMoveStartTime;
    uint64_t unitMoveEndTime;

    void unitTrans(float, float);
    void stop();

public:
    MazeSolver();
    void run();
};

#endif // MAZE_SOLVER_H

