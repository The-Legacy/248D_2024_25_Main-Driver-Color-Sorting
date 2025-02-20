#include "main.h"
#include "pros/motors.hpp"
#include <cmath>

int currState = 0;
const int numStates = 5;
int states[numStates] = {800, 4800, 9272, 17600, 25000}; //0, 528, 1200, 2150, 3200
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
    double kp = .025;
    double error = target - lbRot.get_position();
    double velocity = kp * error;
    if(states[currState] - 40 > error || states[currState] + 40 < error){
        LB.move(velocity);
    } else {
        LB.move(0);
    }
}