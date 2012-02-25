/*! \file maze_solver.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Maze solver bot source.
 */

#include "maze_solver.h"

MazeSolver::MazeSolver() {
    rotSpeed = 0;
    transDir = 0;
    transSpeed = 0;

    unitMoveStartTime = 0;
    unitMoveEndTime = 0;

    moveCounter = 0;
}

void MazeSolver::run() {
    //if (moveCounter < 5) {
    //    if (micros() > unitMoveEndTime) {
    //        unitTrans(0, 0.6);
    //        moveCounter++;
    //    }
    //    calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    //}
    //else {
    //    stop();
    //}

    calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
}

// Translate one cell in some direction.
void MazeSolver::unitTrans(float dir, float speed) {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + UNIT_DISTANCE/speed * 1000000;

    rotSpeed = 0;
    transDir = dir;
    transSpeed = speed;
}

// End of routine.
void MazeSolver::stop() {
    rotSpeed = 0;
    transDir = 0;
    transSpeed = 0;

    calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
}

