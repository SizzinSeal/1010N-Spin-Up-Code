#include "main.h"
#include "config.hpp"
#include "lemlib/api.hpp"
#include "discControl.hpp"

/**
 * @brief fire the catapult with piston boost
 *
 * @param time time to accelerate for
 * @param accel how fast to accelerate
 * @param decel how fast to decelerate
 */
void boost(int time, int accel, int decel) {
    int i = 0;
    for (; i < time; i += 10) {
        leftDrive.move(i * accel);
        rightDrive.move(i * accel);
        pros::delay(10);
    }
    discControl::fireCata();
    pros::delay(250);
    pistonBoost1.set_value(1);
    pistonBoost2.set_value(1);
    for (int j = i; j > 0; j -= decel) {
        leftDrive.move(j * decel);
        rightDrive.move(j * decel);
        pros::delay(10);
    }
}

void accelerate(int time, int accel, int decel) {
    int i = 0;
    for (; i < time; i += 10) {
        leftDrive.move(i * accel);
        rightDrive.move(i * accel);
        pros::delay(10);
    }
    for (int j = i; j > 0; j -= 10) {
        leftDrive.move(i * decel);
        rightDrive.move(i * decel);
        pros::delay(10);
    }
}

void leftStart() {
    chassis.setPose(-62, 32, 90);
    accelerate(50, 10, 1);
    chassis.turnTo(53, 56, 2000);
    for (int i = 0; i < 5; i++) {
        leftDrive.move(i * 10);
        rightDrive.move(i * 10);
        pros::delay(10);
    }
    discControl::fireCata();
    pros::delay(50);
    pistonBoost1.set_value(1);
    pistonBoost2.set_value(1);
    for (int i = 100; i > 0; i -= 10) {
        leftDrive.move(i);
        rightDrive.move(i);
        pros::delay(10);
    }
    chassis.moveTo(-56, 35, 2000);
    chassis.turnTo(-36, 17, 1000);
    chassis.moveTo(-34, 14, 3000, 80);
    discControl::intake();
    leftDrive.move(30);
    rightDrive.move(30);
    pros::delay(1500);
    chassis.turnTo(49, 49, 2000);
    boost(30, 10, 1);
    pros::delay(500);
    chassis.moveTo(-24, 4, 2000);
}

void leftAuto() {
    leftStart();
    chassis.moveTo(-59, -7, 3000);
    chassis.turnTo(-22, -15, 1000);
    discControl::intake();
    chassis.moveTo(-22, -15, 5000, 40);
    chassis.moveTo(-37, -5, 2000);
    chassis.turnTo(48, 58, 1000);
    leftDrive.move(127);
    rightDrive.move(127);
    boost(100, 1, 1);
    pros::delay(150);
    leftDrive.move(-10);
    rightDrive.move(-10);
}

void AWP() {
    leftStart();
    chassis.turnTo(12, -26, 2000);
    pros::delay(500);
    discControl::intake();
    chassis.moveTo(12, -26, 6000, 50);
    chassis.turnTo(53, 53, 2000);
    boost(20, 5, 5);
    pros::delay(500);
    chassis.moveTo(40, -58, 2000);
}

/**
 * @brief runs during the autonomous
 */
void autonomous() { AWP(); }
