/*! \file movements.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Movements for maze solver.
 */

#include "movements.h"

// ============================================================================
// TRANSLATE
//
// Linear movements with zero rotation.
// ============================================================================
void transUnit() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + UNIT_DISTANCE/MAZE_TRANS_SPEED * 1000000;

    rotSpeed = 0;
    transDir = PI/2;
    transSpeed = MAZE_TRANS_SPEED;
}

void transForward() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + 1000;   // Increment by only 1 ms since we need to check for turns.

    rotSpeed = 0;
    transDir = PI/2;
    transSpeed = MAZE_TRANS_SPEED;
}

// ============================================================================
// VEER
//
// Nearly linear movement with slight skew to one side for course corrections.
// ============================================================================
void veerRight() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + 1000;

    rotSpeed = -MAZE_VEER_SPEED;
    transDir = PI/2 * 0.95;
    transSpeed = MAZE_TRANS_SPEED;
}

void veerLeft() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + 1000;

    rotSpeed = MAZE_VEER_SPEED;
    transDir = PI/2 * 1.05;
    transSpeed = MAZE_TRANS_SPEED;
}

// ============================================================================
// TURN
//
// Sharp, non-zero-radius turns for fast change in direction with minimal loss
// of speed.
// ============================================================================
void turnRight() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + (PI/2 * 1.2) / MAZE_TURN_ROT_SPEED * 1000000;

    rotSpeed = -MAZE_TURN_ROT_SPEED;
    transDir = PI/2;
    transSpeed = MAZE_TURN_TRANS_SPEED;
}

void turnLeft() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + (PI/2) / MAZE_TURN_ROT_SPEED * 1000000;

    rotSpeed = MAZE_TURN_ROT_SPEED;
    transDir = PI/2;
    transSpeed = MAZE_TURN_TRANS_SPEED;
}

// ============================================================================
// ROTATE
//
// Zero-radius rotations for maneuvering out of dead ends.
// ============================================================================
void rotateRight() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + (PI/2) / MAZE_ROT_SPEED * 1000000;

    rotSpeed = -MAZE_ROT_SPEED;
    transDir = 0;
    transSpeed = 0;
}

void rotateLeft() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + (PI/2) / MAZE_ROT_SPEED * 1000000;

    rotSpeed = MAZE_ROT_SPEED;
    transDir = 0;
    transSpeed = 0;
}

void rotateBack() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + PI / MAZE_ROT_SPEED * 1000000;

    rotSpeed = MAZE_ROT_SPEED;
    transDir = 0;
    transSpeed = 0;
}

// ============================================================================
// STOP
//
// Stop moving.
// ============================================================================
void stop() {
    unitMoveStartTime = micros();
    unitMoveEndTime = unitMoveStartTime + 1000;

    rotSpeed = 0;
    transDir = 0;
    transSpeed = 0;
}

