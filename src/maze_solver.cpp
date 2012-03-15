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
        if (nextUnitAction == NULL) {
            if (ledReadings[0] < LED_0_THRESHOLD_6CM) {   // No wall to right
                runUnitAction = &turnRight;
                nextUnitAction = &transUnit;
            }
            else if (ledReadings[2] > LED_2_THRESHOLD_10CM) {   // Wall in front.
                if (ledReadings[3] < LED_3_THRESHOLD_6CM) {   // No wall to left?
                    runUnitAction = &rotateLeft;
                }
                else {
                    runUnitAction = &rotateBack;
                }
            }
            else if (ledReadings[2] < LED_2_THRESHOLD_10CM) {   // No wall in front.
                //if (ledReadings[0] > LED_0_THRESHOLD_2CM) {
                //    runUnitAction = &veerLeft;
                //}
                //else if (ledReadings[0] < LED_0_THRESHOLD_6CM) {
                //    runUnitAction = &veerRight;
                //}
                //else {
                    runUnitAction = &transForward;
                //}
            }
        }
        else {
            runUnitAction = nextUnitAction;
            nextUnitAction = NULL;
        }

        runUnitAction();   // Unit controller function pointer.
        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}

