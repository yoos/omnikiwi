/*! \file maze_solver.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Maze solver bot source.
 */

#include "maze_solver.h"

MazeSolver::MazeSolver() {
    rotSpeed = 0;
    transDir = 0;
    transSpeed = 0;

    counter = 0;
}

void MazeSolver::run() {
    counter += 0.01;

    transSpeed = WHEEL_RADIUS * MAX_MOTOR_SPEED * sin(counter);

    calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
}

