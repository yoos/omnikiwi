/*! \file movements.h
 *  \author Soo-Hyun Yoo
 *  \brief Movements for maze solver.
 */

#ifndef MOVEMENTS_H
#define MOVEMENTS_H

uint64_t unitMoveStartTime;
uint64_t unitMoveEndTime;

void (*runUnitAction) ();
void (*nextUnitAction) ();

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

#endif // MOVEMENTS_H

