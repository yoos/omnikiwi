/*! \file globals.h
 *  \author Soo-Hyun Yoo
 *  \brief Various global definitions and variables.
 *
 *  Details.
 */

#ifndef GLOBALS_H
#define GLOBALS_H

// ============================================================================
// Variables
// ============================================================================
int loopCount;   // Count system loops.
uint8_t  digOut[3];   // Motor digital outputs.
float analogOut[3];   // Motor PWM outputs.
float bodyDCM[3][3];   // Current body orientation calculated by IMU.
float targetRot[3], currentRot[3], pidRot[3];


// ============================================================================
// PID
//     Match the number of structs to the number of PID value defines.
// ============================================================================
struct PIDdata {
    float P, I, D;
    float lastValue;
    float integral;
} PID[4];

#define PID_ROT_X 0
#define PID_ROT_Y 1
#define PID_ROT_Z 2

#define XY_P_GAIN 32.0 // 17  30  35  42
#define XY_I_GAIN 10.0 // 10  20  50  24
#define XY_D_GAIN -8.0 //  6  10   9  10

#define Z_P_GAIN 100.0
#define Z_I_GAIN 0.0
#define Z_D_GAIN 0.0

// ============================================================================
// SERIAL IN
// ============================================================================
#define BAUDRATE 115200
#define SERHEAD     255   // Serial header byte. Pilot interprets the four bytes following this header byte as motor commands.
#define PACKETSIZE 6     // Each packet contains (excluding header) X, Y, Twist, Z, and two bytes for button values.
#define INPUT_MIN  0     // Minimum integer input value from joystick.
#define INPUT_MAX  250   // Maximum integer input value from joystick.
#define SX 0   // Serial byte location for joystick X axis.
#define SY 1   // Serial byte location for joystick Y axis.
#define ST 2   // Serial byte location for joystick T (twist) axis.
#define SZ 3   // Serial byte location for joystick Z axis.
#define SB1 4   // Serial byte location for joystick buttons (0 to 7).
#define SB2 5   // Serial byte location for joystick buttons (8 to 15).

// ============================================================================
// SERIAL OUT
// ============================================================================
#define SEND_TARGET_ROTATION
#define SEND_MOTOR_VALUES
#define SEND_DCM
#define SEND_PID

#define DCM_SER_TAG 0xfb
#define ROT_SER_TAG 0xfc
#define MOT_SER_TAG 0xfd
#define PID_SER_TAG 0xfe
#define FIELD_SER_TAG 0xff

// ============================================================================
// Software configuration: any parameter that is purely code-related or is
// relatively frequently changed.
// ============================================================================
#define MASTER_DT           10000   // 10000 us interval = 100 Hz master loop.
#define CONTROL_LOOP_INTERVAL   2   // 1/2 master = 50 Hz. NOTE: This frequency should be HIGHER than comm.py's dataSend frequency!
#define TELEMETRY_LOOP_INTERVAL 2   // 1/2 master = 50 Hz.

#define MOVE_REL_BODY   // Move relative to body.
//#define MOVE_REL_WORLD   // Move relative to world.

#define TMIN 0     // Min analog out.
#define TMAX 255   // Max analog out.

#define MOTOR_T 0   // Tail motor array index.
#define MOTOR_R 1   // Right motor array index.
#define MOTOR_L 2   // Left motor array index.

// ============================================================================
// Buttons
// ============================================================================
#define BUTTON_UNDEFINED            0
#define BUTTON_RESET_YAW            1
#define BUTTON_ZERO_INTEGRAL        2
#define BUTTON_DECREASE_TRIM        3
#define BUTTON_UNDEFINED            4
#define BUTTON_INCREASE_TRIM        5
#define BUTTON_DECREASE_XY_P_GAIN   6
#define BUTTON_INCREASE_XY_P_GAIN   7
#define BUTTON_DECREASE_XY_I_GAIN   8
#define BUTTON_INCREASE_XY_I_GAIN   9
#define BUTTON_DECREASE_XY_D_GAIN   10
#define BUTTON_INCREASE_XY_D_GAIN   11

// ============================================================================
// Hardware configuration: any parameter that is changed so infrequently that
// it may as well be hard-coded.
// ============================================================================
#define ROBOT_RADIUS 0.07   // Robot wheelbase diameter in meters.
#define WHEEL_RADIUS 0.03   // Effective wheel diameter in meters.
#define MAX_MOTOR_SPEED 36.652   // Maximum motor speed in rad/s (350 RPM at 6V).

#define MT_PWM 9   // Tail motor PWM pin.
#define MT_DIG 8   // Tail motor digital pin.
#define MR_PWM 5   // Right motor PWM pin.
#define MR_DIG 4   // Right motor digital pin.
#define ML_PWM 6   // Left motor PWM pin.
#define ML_DIG 7   // Left motor digital pin.


// ============================================================================
// Constants
// ============================================================================
#define PI 3.141592653589793238462643383279502884197f


// ============================================================================
// Functions
// ============================================================================
void zeroStr(char *sStr) {
    for (int i=0; i<sizeof(sStr); i++) {
        sStr[i] = 0;
    }
}

#define sp Serial.print
#define spln Serial.println
#define sw Serial.write

#endif // GLOBALS_H

