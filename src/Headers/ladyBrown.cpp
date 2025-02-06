#include "main.h"
#include "pros/motors.hpp"
#include <cmath>

int currState = 0;
const int numStates = 5;
int states[numStates] = {0, 522, 1000, 2150, 3000};
int target = 0;

void nextState() {
    currState += 1;
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && (currState == 2 || currState == 4)) {
        currState += 1; // Skip the 1200-degree state
    }
    if (currState == numStates) {
        currState = 0;
    }
    target = states[currState];
}

void liftControl() {
    double kp = .4;
    double error = target - LB.get_position();
    double velocity = kp * error;
    LB.move(velocity);
}