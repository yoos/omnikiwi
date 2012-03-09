/*! \file maze_solver.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Maze solver bot source.
 */

#include "maze_solver.h"

MazeSolver::MazeSolver() {
    rotSpeed = 0;
    transDir = 0;
    transSpeed = 0;

    runUnitAction = &stop;

    moveCounter = 0;
}

void MazeSolver::run() {
    //mazeSolver();
    //lightFollower();
    wallFollower();
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
    if (micros() > unitMoveEndTime) {
        if (ledReadings[1] > MAZE_THRESHOLD_NOWALL &&
            ledReadings[2] > MAZE_THRESHOLD_NOWALL) {   // Wall in front.

            if (ledReadings[0] < MAZE_THRESHOLD_NOWALL) {   // No wall to right?
                runUnitAction = &rotateRight;
            }
            else if (ledReadings[3] < MAZE_THRESHOLD_NOWALL) {   // No wall to left?
                runUnitAction = &rotateLeft;
            }
        }
        else if (ledReadings[1] < MAZE_THRESHOLD_NOWALL &&
                 ledReadings[2] < MAZE_THRESHOLD_NOWALL) {   // No wall in front.
            if (ledReadings[0] > ledReadings[3]) {
                runUnitAction = &veerLeft;
            }
            else if (ledReadings[0] < ledReadings[3]) {
                runUnitAction = &veerRight;
            }
        }

        runUnitAction();   // Unit contoller function pointer.
        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}

