/*! \file imu.cpp
 *  \author Soo-Hyun Yoo
 *  \brief Source for IMU class.
 */

#include "imu.h"

IMU::IMU() {
}

void IMU::init() {
    spln("IMU here!");
    update();
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
    //sp("M(");
    //for (int i=0; i<3; i++) {
    //    sp(mag.get(i));
    //    sp(" ");
    //}
    //sp(")  ");
    //sp("H: ");
    //spln(heading);
}

