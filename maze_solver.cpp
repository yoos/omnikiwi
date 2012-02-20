/*! \file maze_solver.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Maze solver bot source.
 */

#include "maze_solver.h"

MazeSolver::MazeSolver() {
}

void MazeSolver::run() {
    calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
}

