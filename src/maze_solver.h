/*! \file maze_solver.h
 *  \author Soo-Hyun Yoo
 *  \brief Maze solver bot.
 */

#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "globals.h"
#include "motors.h"
#include "movements.cpp"
#include "lsm303.cpp"

class MazeSolver {
    // Sensors
    LSM303 mag;

    // Controllers
    void mazeSolver();
    void lightFollower();
    void wallFollower();

    bool okayToTurnRight;

    // Current and target wall "statuses", i.e., whether or not there is a wall to the right, front, left, and back.
    uint8_t currentWalls[4];
    uint8_t targetWalls[4];
    uint8_t lastWalls[4];

    void updateWalls();

public:
    MazeSolver();
    void run();
};

#endif // MAZE_SOLVER_H

