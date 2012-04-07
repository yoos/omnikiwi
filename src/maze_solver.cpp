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

    okayToTurnRight = true;

    for (int i=0; i<4; i++) {
        currentWalls[i] = 0;
        targetWalls[i] = 0;
        lastWalls[i] = 0;
    }
}

void MazeSolver::run() {
    updateWalls();
    //mazeSolver();
    //lightFollower();
    wallFollower();
}

void MazeSolver::mazeSolver() {
    //if (micros() > unitMoveEndTime) {
    //    if (ledReadings[2] < MAZE_THRESHOLD_FORWARD) {   // Nothing ahead.
    //        if (ledReadings[0] > MAZE_THRESHOLD_RIGHT_HIGH) {   // Right wall too close
    //            runUnitAction = &veerLeft;
    //        }
    //        else if (ledReadings[0] < MAZE_THRESHOLD_RIGHT_LOW) {
    //            runUnitAction = &veerRight;
    //        }
    //        else {
    //            runUnitAction = &transForward;
    //        }
    //    }
    //    else {
    //        runUnitAction = &rotateRight;
    //    }

    //    if (ledReadings[3] < MAZE_THRESHOLD_NOWALL) {
    //        runUnitAction = &rotateLeft;
    //    }

    //    runUnitAction();   // Unit controller function pointer.
    //    calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    //}
}

void MazeSolver::lightFollower() {
    //bool stimulus = false;

    //float ledDir = 0;
    //for (int i=0; i<NUM_OF_LEDS; i++) {
    //    if (ledReadings[i] > MAZE_THRESHOLD_FORWARD) {
    //        ledDir = PI/3 * i;
    //        stimulus = true;
    //    }
    //}

    //if (stimulus) {
    //    transDir = ledDir;
    //    transSpeed = MAZE_TRANS_SPEED;
    //}
    //else {
    //    transSpeed = 0;
    //}
}

void MazeSolver::wallFollower() {
    if (micros() > unitMoveEndTime) {
        if (nextUnitAction == NULL) {
            if (!currentWalls[0]) {   // No wall to right
                if (okayToTurnRight) {
                    runUnitAction = &turnRight;
                    nextUnitAction = &transUnit;

                    //for (int i=0; i<4; i++) {
                    //    lastWalls[i] = currentWalls[(i-1)%4];
                    //}
                    //okayToTurnRight = false;
                }
                else {
                    if (currentWalls[1]) {
                        runUnitAction = &rotateLeft;
                    }
                    else {
                        runUnitAction = &transForward;
                    }
                }
            }
            else if (currentWalls[1]) {   // Wall in front.
                if (!currentWalls[2]) {   // No wall to left?
                    runUnitAction = &rotateLeft;
                }
                else {
                    runUnitAction = &rotateBack;
                }
            }
            else if (!currentWalls[1]) {   // No wall in front.
                //if (ledFiltered[1] > MAZE_THRESHOLD_RIGHT_AHEAD) {
                //    runUnitAction = &veerLeft;
                //}
                //else if (ledFiltered[5] > MAZE_THRESHOLD_RIGHT_BEHIND) {
                //    runUnitAction = &veerRight;
                //}
                //else {
                runUnitAction = &transForward;
                //}

                for (int i=0; i<4; i++) {
                    if (currentWalls[i] != lastWalls[i]) {
                        okayToTurnRight = true;
                    }
                }
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

void MazeSolver::updateWalls() {
    currentWalls[0] = (ledFiltered[0] > MAZE_THRESHOLD_RIGHT) ? 1 : 0;
    currentWalls[1] = (ledFiltered[1] > MAZE_THRESHOLD_FRONT) ? 1 : 0;
    currentWalls[2] = (ledFiltered[2] > MAZE_THRESHOLD_LEFT)  ? 1 : 0;
    currentWalls[3] = (ledFiltered[3] > MAZE_THRESHOLD_BACK)  ? 1 : 0;
}
