#include "main.h"
#include "config.hpp"
#include "lemlib/api.hpp"
#include "discControl.hpp"

/**
 * @brief screen updater function
 *
 */
void screenUpdater() {
    // initialize llemu
    pros::lcd::initialize();
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose();
        pros::lcd::print(0, "x: %f", pose.x);
        pros::lcd::print(1, "y: %f", pose.y);
        pros::lcd::print(2, "theta: %f", pose.theta);
        pros::delay(16);
    }
}

/**
 * @brief runs as soon as the program starts. Used to calibrate sensors and start threads
 */
void initialize() {
    // calibrate sensors on the chassis
    chassis.calibrate(); // approx 3 seconds
    // start subsystem controller
    discControl::initialize();
    // start screen updater task
    pros::Task screen(screenUpdater);
}

/**
 * @brief driver control code
 */
void opcontrol() {
    // calculate constants for expo drive
    // it wont let me make this constexpr ;-;
    const float lateralB = 1.0 / std::pow(127, LATERAL_EXPO_COEFFICIENT - 1);
    const float angularB = 1.0 / std::pow(127, ANGULAR_EXPO_COEFFICIENT - 1);
    // main loop
    while (true) {
        // control the disc manipulator
        if (master.get_digital_new_press(CATA_FIRE_BUTTON)) {
            discControl::fireCata();
            pros::delay(200);
            pistonBoost1.set_value(1);
            pistonBoost2.set_value(1);
        } else if (master.get_digital(INTAKE_BUTTON)) {
            discControl::intake();
        } else {
            discControl::stop();
        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) pistonBoost1.set_value(1);
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) pistonBoost2.set_value(1);

        // control the drivetrain
        float rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        float leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // apply expo drive
        float forward = lemlib::sgn(leftY) * std::pow(std::fabs(leftY), LATERAL_EXPO_COEFFICIENT) * lateralB;
        float angular = lemlib::sgn(rightX) * std::pow(std::fabs(rightX), ANGULAR_EXPO_COEFFICIENT) * angularB;
        // calculate motor speeds
        float left = forward + angular;
        float right = forward - angular;
        // desaturate velocities
        float max = std::max(std::fabs(left), std::fabs(right)) / 127;
        if (max > 1) {
            left /= max;
            right /= max;
        }
        // set the motor speeds
        leftDrive.move(left);
        rightDrive.move(right);

        // delay to save resources
        pros::delay(10);
    }
}

/**
 * @brief runs during disabled
 *
 * this runs whenever the robot is disabled by the field controller
 * runs after initialize
 */
void disabled() {}
