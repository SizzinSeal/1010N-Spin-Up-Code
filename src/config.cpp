#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h"
#include "lemlib/api.hpp"
#include "config.hpp"

// motors
pros::Motor leftBackDrive(LEFT_BACK_DRIVE_PORT, LEFT_BACK_DRIVE_GEARBOX, LEFT_BACK_DRIVE_REVERSED);
pros::Motor leftMidDrive(LEFT_MID_DRIVE_PORT, LEFT_MID_DRIVE_GEARBOX, LEFT_MID_DRIVE_REVERSED);
pros::Motor leftFrontDrive(LEFT_FRONT_DRIVE_PORT, LEFT_FRONT_DRIVE_GEARBOX, LEFT_FRONT_DRIVE_REVERSED);
pros::Motor rightBackDrive(RIGHT_BACK_DRIVE_PORT, RIGHT_BACK_DRIVE_GEARBOX, RIGHT_BACK_DRIVE_REVERSED);
pros::Motor rightMidDrive(RIGHT_MID_DRIVE_PORT, RIGHT_MID_DRIVE_GEARBOX, RIGHT_MID_DRIVE_REVERSED);
pros::Motor rightFrontDrive(RIGHT_FRONT_DRIVE_PORT, RIGHT_FRONT_DRIVE_GEARBOX, RIGHT_FRONT_DRIVE_REVERSED);
pros::Motor leftGeneralMotor(LEFT_GENERAL_MOTOR_PORT, LEFT_GENERAL_MOTOR_GEARBOX, LEFT_GENERAL_MOTOR_REVERSED);
pros::Motor rightGeneralMotor(RIGHT_GENERAL_MOTOR_PORT, RIGHT_GENERAL_MOTOR_GEARBOX, RIGHT_GENERAL_MOTOR_REVERSED);
pros::MotorGroup leftDrive({leftBackDrive, leftMidDrive, leftFrontDrive});
pros::MotorGroup rightDrive({rightBackDrive, rightMidDrive, rightFrontDrive});

// sensors
pros::Rotation cataRot(CATA_ROTATION_PORT, CATA_ROTATION_REVERSED);
pros::Distance chamberDistance(CHAMBER_DISTANCE_PORT);
pros::Distance intakeDistance(INTAKE_DISTANCE_PORT);
pros::Imu inertialSensor(INERTIAL_SENSOR_PORT);
pros::ADIEncoder trackingWheelEncoder(TRACKING_WHEEL_PORT_1, TRACKING_WHEEL_PORT_2, TRACKING_WHEEL_REVERSED);

// pneumatics
pros::ADIDigitalOut intakeLift(INTAKE_LIFT_PORT);
pros::ADIDigitalOut pistonBoost1(PISTON_BOOST_1_PORT);
pros::ADIDigitalOut pistonBoost2(PISTON_BOOST_2_PORT);
pros::ADIDigitalOut pto(PTO_PORT);

// controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);

// lemlib objects
lemlib::TrackingWheel trackingWheel(&trackingWheelEncoder, TRACKING_WHEEL_DIAMETER, TRACKING_WHEEL_DISTANCE);
lemlib::OdomSensors_t odomSensors {nullptr, nullptr, &trackingWheel, nullptr, &inertialSensor};
lemlib::Drivetrain_t drivetrain {&leftDrive, &rightDrive, TRACK_WIDTH, WHEEL_DIAMETER, SPEED_RPM};
lemlib::ChassisController_t linearController {LINEAR_KP,
                                              LINEAR_KD,
                                              LINEAR_SMALL_ERROR_THRESHOLD,
                                              LINEAR_SMALL_ERROR_TIMEOUT,
                                              LINEAR_LARGE_ERROR_THRESHOLD,
                                              LINEAR_LARGE_ERROR_TIMEOUT,
                                              LINEAR_SLEW};
lemlib::ChassisController_t angularController {ANGULAR_KP,
                                               ANGULAR_KD,
                                               ANGULAR_SMALL_ERROR_THRESHOLD,
                                               ANGULAR_SMALL_ERROR_TIMEOUT,
                                               ANGULAR_LARGE_ERROR_THRESHOLD,
                                               ANGULAR_LARGE_ERROR_TIMEOUT,
                                               ANGULAR_SLEW};
lemlib::Chassis chassis(drivetrain, linearController, angularController, odomSensors);
