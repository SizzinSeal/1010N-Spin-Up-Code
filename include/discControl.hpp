#pragma once

namespace discControl {
enum Mode {
    SwithToCata = 0,
    SwitchToDrive = 1,
    Driving = 2,
    Firing = 3,
    Loading = 4,
    Stop = 5,
    Intaking = 6,
    Idle = 7
};

void initialize();
void fireCata();
void intake();
void stop();
Mode getMode();
}; // namespace discControl
