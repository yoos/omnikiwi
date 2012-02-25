/*! \file maze_solver.h
 *  \author Soo-Hyun Yoo
 *  \brief Maze solver bot.
 */

#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "globals.h"
#include "motors.h"

uint64_t unitMoveStartTime;
uint64_t unitMoveEndTime;

void (*runUnitAction) ();

void transUnit();
void transForward();

void veerRight();
void veerLeft();

void turnRight();
void turnLeft();

void rotateRight();
void rotateLeft();
void rotateBack();

void stop();


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

