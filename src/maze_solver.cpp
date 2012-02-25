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
    if (ledReadings[2] < MAZE_FORWARD_THRES) {   // Nothing ahead.
        if (ledReadings[0] > MAZE_RIGHT_THRES_HIGH) {   // Right wall too close
            runUnitAction = &veerLeft;
        }
        else if (ledReadings[0] < MAZE_RIGHT_THRES_LOW) {
            runUnitAction = &veerRight;
        }
        else {
            runUnitAction = &transForward;
        }
    }
    else {
        runUnitAction = &rotateRight;
    }

    if (ledReadings[3] < MAZE_LEFT_THRES_NOWALL) {
        runUnitAction = &rotateLeft;
    }

    calculate_pwm_outputs(rotSpeed, transDir, transSpeed);

    if (micros() > unitMoveEndTime) {
        runUnitAction();   // Unit controller function pointer.
    }
    //else {
    //    stop();
    //}
}

void MazeSolver::lightFollower() {
    bool stimulus = false;

    float ledDir = 0;
    for (int i=0; i<NUM_OF_LEDS; i++) {
        if (ledReadings[i] > LED_TRIGGER_THRESHOLD) {
            ledDir = PI/3 * i;
            stimulus = true;
        }
    }

    if (stimulus) {
        transDir = ledDir;
        transSpeed = 0.8;
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


// Translate one cell in some direction.
void unitTrans() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + UNIT_DISTANCE/MAZE_TRANS_SPEED * 1000000;

    rotSpeed = 0;
    transDir = PI/2;
    transSpeed = MAZE_TRANS_SPEED;

    calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
}

void transForward() {
    if (micros() > unitMoveEndTime) {
        unitMoveStartTime = micros();
        unitMoveEndTime = unitMoveStartTime + 1000;   // Increment by only 1 ms since we need to check for turns.

        rotSpeed = 0;
        transDir = PI/2;
        transSpeed = MAZE_TRANS_SPEED;

        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}

void rotateRight() {
    if (micros() > unitMoveEndTime) {
        unitMoveStartTime = micros();
        unitMoveEndTime = unitMoveStartTime + (PI/2) / MAZE_ROT_SPEED * 1000000;

        rotSpeed = -MAZE_ROT_SPEED;
        transDir = 0;
        transSpeed = 0;

        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}

void rotateLeft() {
    if (micros() > unitMoveEndTime) {
        unitMoveStartTime = micros();
        unitMoveEndTime = unitMoveStartTime + (PI/2) / MAZE_ROT_SPEED * 1000000;

        rotSpeed = MAZE_ROT_SPEED;
        transDir = 0;
        transSpeed = 0;

        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}

void rotateBack() {
    if (micros() > unitMoveEndTime) {
        unitMoveStartTime = micros();
        unitMoveEndTime = unitMoveStartTime + PI / MAZE_ROT_SPEED * 1000000;

        rotSpeed = MAZE_ROT_SPEED;
        transDir = 0;
        transSpeed = 0;

        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}

void veerRight() {
    if (micros() > unitMoveEndTime) {
        unitMoveStartTime = micros();
        unitMoveEndTime = unitMoveStartTime + 1000;

        rotSpeed = -MAZE_VEER_SPEED;
        transDir = PI/2;
        transSpeed = MAZE_TRANS_SPEED;

        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}

void veerLeft() {
    if (micros() > unitMoveEndTime) {
        unitMoveStartTime = micros();
        unitMoveEndTime = unitMoveStartTime + 1000;

        rotSpeed = MAZE_VEER_SPEED;
        transDir = PI/2;
        transSpeed = MAZE_TRANS_SPEED;

        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}


// End of routine.
void stop() {
    if (micros() > unitMoveEndTime) {
        unitMoveStartTime = micros();
        unitMoveEndTime = unitMoveStartTime + 1000;

        rotSpeed = 0;
        transDir = 0;
        transSpeed = 0;

        calculate_pwm_outputs(rotSpeed, transDir, transSpeed);
    }
}

