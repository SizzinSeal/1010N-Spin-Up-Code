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
                leftGeneralMotor.move(-127);
                rightGeneralMotor.move(-127);
                // check if the catapult has fired yet
                if (angle < 5000 || angle > 32000) { mode = discControl::Loading; }
                break;
            }
            // load the catapult
            case discControl::Loading: {
                // check if the catapult is down
                if ((angle < CATA_LOADING_ANGLE + 50 && angle > 20000)) {
                    mode = discControl::Idle;
                    break;
                }
                // update the PID
                float output = cataPID.update(CATA_LOADING_ANGLE, angle);
                output -= CATA_FEEDFORWARD;
                // move the catapult
                leftGeneralMotor.move(output);
                rightGeneralMotor.move(output);
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
                pros::lcd::print(0, "left wattage: %f", leftGeneralMotor.get_power());
                pros::lcd::print(1, "right wattage: %f", rightGeneralMotor.get_power());
                break;
            }
            // idle
            case discControl::Idle: {
                leftGeneralMotor.move(0);
                rightGeneralMotor.move(0);
                break;
            }
        }
        pros::delay(10);
    }
}

void discControl::initialize() {
    if (cataTask == nullptr) cataTask = new pros::Task([=]() { cataUpdater(); });
}

void discControl::fireCata() { request = discControl::Mode::Firing; }

void discControl::intake() { request = discControl::Mode::Intaking; }

void discControl::stop() { request = discControl::Mode::Stop; }

discControl::Mode discControl::getMode() { return mode; }
