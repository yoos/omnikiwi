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
uint8_t digOut[3];    // Motor digital outputs.
float analogOut[3];   // Motor PWM outputs.
float bodyDCM[3][3];   // Current body orientation calculated by IMU.
float targetRot[3], currentRot[3], pidRot[3];
float rotSpeed, transDir, transSpeed;

uint16_t moveCounter;

uint16_t chargeReadings[6], ledReadings[6];   // LED distance sensor readings.


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
#define BAUDRATE  57600
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
#define SEND_MOVE_COUNTER
#define SEND_TARGET_ROTATION
//#define SEND_MOTOR_VALUES
#define SEND_SENSOR_READINGS
//#define SEND_DCM
//#define SEND_PID
//#define SEND_DIR

#define SEN_SER_TAG 0xfb
#define ROT_SER_TAG 0xfc
#define MOT_SER_TAG 0xfd
#define PID_SER_TAG 0xfe
#define FIELD_SER_TAG 0xff

// ============================================================================
// Software configuration: any parameter that is purely code-related or is
// relatively frequently changed.
// ============================================================================
// TODO: might want to consider changing MASTER_DT back to 8000 or changing the
// sensor lead count from 2 to 3.
#define MASTER_DT            5200   // 8000 us interval = 125 Hz master loop.
#define CONTROL_LOOP_INTERVAL   2   // 2x master = 62.5 Hz. NOTE: This frequency should be HIGHER than comm.py's dataSend frequency!
#define SENSOR_LOOP_INTERVAL    6   // 1/6 master = 20.83 Hz.
#define TELEMETRY_LOOP_INTERVAL 4   // 1/4 master = 31.25 Hz.

#define MOVE_REL_BODY   // Move relative to body.
//#define MOVE_REL_WORLD   // Move relative to world.

#define TMIN 0     // Min analog out.
#define TMAX 255   // Max analog out.

#define MOTOR_T 0   // Tail motor array index.
#define MOTOR_R 1   // Right motor array index.
#define MOTOR_L 2   // Left motor array index.

// Maze solver
#define COV019
//#define KELLEY

#define UNIT_DISTANCE 0.3   // "Unit" distance for maze solver.
#define UNIT_ROT (PI/2)     // "Unit" rotation for maze solver.

#define MAZE_TRANS_SPEED 1.0
#define MAZE_VEER_SPEED  0.1
#define MAZE_TURN_SPEED  2.0
#define MAZE_ROT_SPEED   4.0

#ifdef COV019
uint16_t ledZero[] = {260, 0, 0, 0, 0, 0};
#define LED_MAX_SANE_READING 500

#define MAZE_THRESHOLD_4CM 450
#define MAZE_THRESHOLD_6CM 400
#define MAZE_THRESHOLD_8CM 300
#define MAZE_THRESHOLD_10CM 250
#endif // COV019

#ifdef KELLEY
uint16_t ledZero[] = {0, 0, 0, 0, 0, 0};
#define LED_MAX_SANE_READING 500

#define MAZE_FORWARD_THRES 600
#define MAZE_RIGHT_THRES_LOW  400
#define MAZE_RIGHT_THRES_HIGH 540
#define MAZE_LEFT_THRES_NOWALL 300
#endif // KELLEY

#define MAZE_THRESHOLD_FORWARD    MAZE_THRESHOLD_6CM
#define MAZE_THRESHOLD_RIGHT_HIGH MAZE_THRESHOLD_4CM
#define MAZE_THRESHOLD_RIGHT_LOW  MAZE_THRESHOLD_6CM
#define MAZE_THRESHOLD_NOWALL     MAZE_THRESHOLD_10CM


// Sensors
//#define LED_DISCHARGE_TIME 17   // Time in milliseconds.


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
#define ROBOT_RADIUS 0.071   // Robot wheelbase radius in meters.
#define WHEEL_RADIUS 0.0254   // Effective wheel radius in meters.
#define MAX_MOTOR_SPEED 73.304   // Maximum motor speed in rad/s (350 RPM at 6V == 700 RPM at 12 V). TODO: This varies based on battery voltage. Either make this dynamic or implement rotation sensing using a gyro or encoders.
#define NUM_OF_LEDS 6   // Number of LED sensors.

// Digital pin assignments
#define MT_DIG 2   // Tail motor digital pin.
#define MT_PWM 3   // Tail motor PWM pin.
#define MR_DIG 4   // Right motor digital pin.
#define MR_PWM 5   // Right motor PWM pin.
#define ML_PWM 6   // Left motor PWM pin.
#define ML_DIG 7   // Left motor digital pin.

// Following six pins used as LED anodes.
//#define UNDEF_PIN 8
//#define UNDEF_PIN 9
//#define UNDEF_PIN 10
//#define UNDEF_PIN 11
//#define UNDEF_PIN 12
//#define UNDEF_PIN 13

// LED pins
static int anodePins[]   = {8, 9, 10, 11, 12, 13};
static int cathodePins[] = {14, 15, 16, 17, 18, 19};


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

