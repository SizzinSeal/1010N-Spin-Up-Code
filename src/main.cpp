#include "main.h"
#include "config.hpp"
#include "lemlib/api.hpp"
#include "discControl.hpp"

void initialize() { discControl::initialize(); }

void opcontrol() {
    pros::lcd::initialize();
    while (true) {
        // control the disc manipulator
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
            discControl::fireCata();
        } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
            if (discControl::getMode() == discControl::Mode::Intaking) {
                discControl::stop();
            } else {
                discControl::intake();
            }
        }

        // control the drivetrain
        float angular = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 0.6;
        float forward = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // calculate motor speeds
        float left = forward + angular;
        float right = forward - angular;
        // balance the motor speeds
        float max = std::max(std::abs(left), std::abs(right));
        if (max > 127) {
            left /= max;
            right /= max;
        }
        // set the motor speeds
        leftDrive.move(left);
        rightDrive.move(right);

        pros::delay(10);
    }
}

void autonomous() {}

void disabled() {}
