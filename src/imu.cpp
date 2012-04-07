/*! \file imu.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Source for IMU class.
 */

#include "imu.h"

IMU::IMU() {
}

void IMU::init() {
    spln("IMU here!");
}

void IMU::update() {
    // ========================================================================
    // Magnetometer
    //     Frame of reference: BODY
    //     Units: N/A
    //     Purpose: Measure the magnetic north vector mVec with components
    //              codirectional with the body's i, j, and k vectors.
    // ========================================================================
    mag.poll();
    heading = mag.getHeading();
    sp("H: ");
    spln(heading);
}

