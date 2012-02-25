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

    mazeSolver();
    //wallFollower();

}

void MazeSolver::mazeSolver() {
    if (micros() > unitMoveEndTime) {
        if (ledReadings[2] < MAZE_THRESHOLD_FORWARD) {   // Nothing ahead.
            if (ledReadings[0] > MAZE_THRESHOLD_RIGHT_HIGH) {   // Right wall too close
                runUnitAction = &veerLeft;
            }
            else if (ledReadings[0] < MAZE_THRESHOLD_RIGHT_LOW) {
                runUnitAction = &veerRight;
            }
            else {
                runUnitAction = &transForward;
            }
        }
        else {
            runUnitAction = &rotateRight;
        }

        if (ledReadings[3] < MAZE_THRESHOLD_NOWALL) {
            runUnitAction = &rotateLeft;
        }

        runUnitAction();   // Unit controller function pointer.
        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}

void MazeSolver::lightFollower() {
    bool stimulus = false;

    float ledDir = 0;
    for (int i=0; i<NUM_OF_LEDS; i++) {
        if (ledReadings[i] > MAZE_THRESHOLD_8CM) {
            ledDir = PI/3 * i;
            stimulus = true;
        }
    }

    if (stimulus) {
        transDir = ledDir;
        transSpeed = MAZE_TRANS_SPEED;
    }
    else {
        transSpeed = 0;
    }
}

void MazeSolver::wallFollower() {
    transDir = PI/2;
    transSpeed = MAZE_TRANS_SPEED;

    if (ledReadings[0] > 590 && ledReadings[1] < 600) {
        rotSpeed = 2;
    }
    else if (ledReadings[0] < 490 && ledReadings[1] < 600) {
        rotSpeed = -2;
    }
    else if (ledReadings[1] < 600) {
        rotSpeed = 0;
    }

    calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
}

