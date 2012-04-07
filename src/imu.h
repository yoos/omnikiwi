/*! \file imu.h
 *  \author Soo-Hyun Yoo
 *  \brief Header for IMU class.
 *
 *  Details.
 */

#ifndef IMU_H
#define IMU_H

#include "lsm303.cpp"
#include "globals.h"

class IMU {
    LSM303 mag;

public:
    IMU();
    void init();
    void update();
};

#endif // IMU_H

