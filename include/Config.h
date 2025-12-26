#pragma once

#define Ts_us 2000
#define Ts_s (Ts_us / 1000000.0)

// VE
#define VE_LPF_T 0.05

// Servo motor
#define SERVO_KP 3.0
#define SERVO_KI 20.0

// Robot
#define ROBOT_WIDTH 0.075 // [m]
#define ROBOT_WHEEL_RADIUS 0.0165 // [m]

// Movement parameters
#define MAX_VEL 0.10 // [m/s]
#define MAX_ANG_VEL 1.0 // [rad/s]

#define TURN_RADIUS_SHORTEST 0.05 // [m]

// Maze parameters
#define CELL_WIDHT 0.18 // [m]

// ASMR parameters
#define ASMR_PROG_BUFFER_SIZE 64