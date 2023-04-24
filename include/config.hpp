#pragma once

#include "main.h"
#include "lemlib/api.hpp"

// controls
#define CATA_FIRE_BUTTON pros::E_CONTROLLER_DIGITAL_L2
#define INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_R2
#define LATERAL_EXPO_COEFFICIENT 1
#define ANGULAR_EXPO_COEFFICIENT 1.5

// motor ports
#define LEFT_BACK_DRIVE_PORT 2
#define LEFT_MID_DRIVE_PORT 1
#define LEFT_FRONT_DRIVE_PORT 14
#define RIGHT_BACK_DRIVE_PORT 19
#define RIGHT_MID_DRIVE_PORT 21
#define RIGHT_FRONT_DRIVE_PORT 20
#define LEFT_GENERAL_MOTOR_PORT 15
#define RIGHT_GENERAL_MOTOR_PORT 17

// motor reversals
#define LEFT_BACK_DRIVE_REVERSED true
#define LEFT_MID_DRIVE_REVERSED true
#define LEFT_FRONT_DRIVE_REVERSED true
#define RIGHT_BACK_DRIVE_REVERSED false
#define RIGHT_MID_DRIVE_REVERSED false
#define RIGHT_FRONT_DRIVE_REVERSED false
#define LEFT_GENERAL_MOTOR_REVERSED false
#define RIGHT_GENERAL_MOTOR_REVERSED true

// motor gearboxes
#define LEFT_BACK_DRIVE_GEARBOX pros::E_MOTOR_GEARSET_06
#define LEFT_MID_DRIVE_GEARBOX pros::E_MOTOR_GEARSET_06
#define LEFT_FRONT_DRIVE_GEARBOX pros::E_MOTOR_GEARSET_06
#define RIGHT_BACK_DRIVE_GEARBOX pros::E_MOTOR_GEARSET_06
#define RIGHT_MID_DRIVE_GEARBOX pros::E_MOTOR_GEARSET_06
#define RIGHT_FRONT_DRIVE_GEARBOX pros::E_MOTOR_GEARSET_06
#define LEFT_GENERAL_MOTOR_GEARBOX pros::E_MOTOR_GEARSET_18
#define RIGHT_GENERAL_MOTOR_GEARBOX pros::E_MOTOR_GEARSET_18

// sensor ports
#define CATA_ROTATION_PORT 18
#define CHAMBER_DISTANCE_PORT 19
#define INTAKE_DISTANCE_PORT 20
#define INERTIAL_SENSOR_PORT 8
#define TRACKING_WHEEL_PORT_1 'A'
#define TRACKING_WHEEL_PORT_2 'B'

// sensor configurations
#define CATA_ROTATION_REVERSED false
#define TRACKING_WHEEL_REVERSED true
#define TRACKING_WHEEL_DISTANCE -5.5
#define TRACKING_WHEEL_DIAMETER 2.75

// pneumatic ports
#define INTAKE_LIFT_PORT 'G'
#define PISTON_BOOST_1_PORT 'F'
#define PISTON_BOOST_2_PORT 'H'
#define PTO_PORT 'D'

// disc control tuning
#define CATA_LOADING_ANGLE 29150
#define CATA_FIRE_DELAY 300
#define CATA_FEEDFORWARD -50
#define CATA_KP 0.1
#define CATA_KD 0

// chassis configuration
#define TRACK_WIDTH 11
#define WHEEL_DIAMETER 3.25
#define SPEED_RPM 450

// linear control gains
#define LINEAR_KP 8
#define LINEAR_KD 30
#define LINEAR_SMALL_ERROR_THRESHOLD 1
#define LINEAR_SMALL_ERROR_TIMEOUT 100
#define LINEAR_LARGE_ERROR_THRESHOLD 3
#define LINEAR_LARGE_ERROR_TIMEOUT 500
#define LINEAR_SLEW 5

// angular control gains
#define ANGULAR_KP 8
#define ANGULAR_KD 80
#define ANGULAR_SMALL_ERROR_THRESHOLD 1
#define ANGULAR_SMALL_ERROR_TIMEOUT 100
#define ANGULAR_LARGE_ERROR_THRESHOLD 3
#define ANGULAR_LARGE_ERROR_TIMEOUT 500
#define ANGULAR_SLEW 0

// global objects

// motors
extern pros::Motor leftBackDrive;
extern pros::Motor leftMidDrive;
extern pros::Motor leftFrontDrive;
extern pros::Motor rightBackDrive;
extern pros::Motor rightMidDrive;
extern pros::Motor rightFrontDrive;
extern pros::Motor leftGeneralMotor;
extern pros::Motor rightGeneralMotor;
extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;

// sensors
extern pros::Rotation cataRot;
extern pros::Distance chamberDistance;
extern pros::Distance intakeDistance;

// pneumatics
extern pros::ADIDigitalOut intakeLift;
extern pros::ADIDigitalOut pistonBoost1;
extern pros::ADIDigitalOut pistonBoost2;
extern pros::ADIDigitalOut pto;

// controllers
extern pros::Controller master;

// lemlib objects
extern lemlib::TrackingWheel trackingWheel;
extern lemlib::Chassis chassis;
