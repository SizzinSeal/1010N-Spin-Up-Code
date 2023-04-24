#include "main.h"
#include "discControl.hpp"
#include "lemlib/pid.hpp"
#include "config.hpp"

// global variables
pros::Task* cataTask = nullptr;
discControl::Mode mode = discControl::Mode::Loading;

discControl::Mode request = discControl::Mode::Idle;

void cataUpdater() {
    lemlib::FAPID cataPID(0, 0, CATA_KP, 0, CATA_KD, "cata");
    leftGeneralMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightGeneralMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    int fireStart = 0;
    while (true) {
        // get the position of the catapult
        int angle = cataRot.get_angle();

        // update the mode based on the priority of the request
        if (request < mode) mode = request;
        request = discControl::Idle;

        switch (mode) {
            // fire the catapult
            case discControl::Firing: {
                // move the catapult down
                if (!fireStart) {
                    leftGeneralMotor.move(-127);
                    rightGeneralMotor.move(-127);
                }
                // check if the catapult has fired yet
                if ((angle < 5000 || angle > CATA_LOADING_ANGLE + 300) && !fireStart) {
                    fireStart = pros::millis();
                    leftGeneralMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                    rightGeneralMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                    leftGeneralMotor.move(0);
                    rightGeneralMotor.move(0);
                }
                // fire delay
                if (fireStart != 0 && pros::millis() - CATA_FIRE_DELAY > fireStart) {
                    fireStart = 0;
                    mode = discControl::Loading;
                    leftGeneralMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                    rightGeneralMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                }
                break;
            }
            // load the catapult
            case discControl::Loading: {
                // deactivate piston boost
                // activate piston boost
                pistonBoost1.set_value(false);
                pistonBoost2.set_value(false);
                // check if the catapult is down
                if ((angle < CATA_LOADING_ANGLE + 50 && angle > 20000)) {
                    mode = discControl::Idle;
                    break;
                }
                // update the PID
                float output = cataPID.update(CATA_LOADING_ANGLE, angle);
                output += CATA_FEEDFORWARD;
                // move the catapult
                if (angle < 10000) {
                    leftGeneralMotor.move(-127);
                    rightGeneralMotor.move(-127);
                } else {
                    leftGeneralMotor.move(output);
                    rightGeneralMotor.move(output);
                }
                break;
            }
            // stop the intake
            case discControl::Stop: {
                leftGeneralMotor.move(0);
                rightGeneralMotor.move(0);
                // set the mode to idle
                mode = discControl::Idle;
                break;
            }
            // spin the intake
            case discControl::Intaking: {
                leftGeneralMotor.move(127);
                rightGeneralMotor.move(127);
                break;
            }
            // idle
            case discControl::Idle: {
                leftGeneralMotor.move(0);
                rightGeneralMotor.move(0);
                break;
            };
        }
        pros::delay(10);
    }
}

void discControl::initialize() {
    // prevent tomfoolery with the task being initialized twice
    if (cataTask == nullptr) cataTask = new pros::Task([=]() { cataUpdater(); });
}

void discControl::fireCata() { request = discControl::Mode::Firing; }

void discControl::intake() { request = discControl::Mode::Intaking; }

void discControl::stop() { request = discControl::Mode::Stop; }

discControl::Mode discControl::getMode() { return mode; }
