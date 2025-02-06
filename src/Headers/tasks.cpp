#include "main.h"
#include "pros/rtos.hpp"

void odomTask() {
    console.printf("The robot's heading is %f\n", imu.get_heading());
    console.printf("The robot's x position is %f\n", chassis.getPose().x);
    console.printf("The robot's y position is %f\n", chassis.getPose().y);
    pros::delay(50);
}

void LBTask() {
    while (true) {
        liftControl();
        pros::delay(10);
    }
}

void colorSortingBlue(){
    opSense.set_led_pwm(100);
    opSense.set_integration_time(25);
    while (true) {
        // Run the intake motors
        hooks.move_velocity(-600);
        preroller.move_velocity(-200);

        if (opSense.get_hue() < 30) {
            // Reverse the hook motor if it is going too slow
            hooks.move_velocity(600);
            pros::delay(150); // Delay to allow the motor to reverse
            hooks.move_velocity(-600); // Resume normal operation
        }

        pros::delay(50); // Small delay to prevent excessive CPU usage
    }
}

void colorSortingRed(){
    opSense.set_led_pwm(100);
    opSense.set_integration_time(25);
    while (true) {
        // Run the intake motors
        hooks.move_velocity(-600);
        preroller.move_velocity(-200);

        if (opSense.get_hue() > 180) {
            // Reverse the hook motor if it is going too slow
            hooks.move_velocity(600);
            pros::delay(150); // Delay to allow the motor to reverse
            hooks.move_velocity(-600); // Resume normal operation
        }

        pros::delay(50); // Small delay to prevent excessive CPU usage
    }
}

void intakeTask() {
    uint32_t lastCheckTime = pros::millis();

    while (true) {
        // Run the intake motors
        hooks.move_velocity(-600);
        preroller.move_velocity(-200);

        // Check if a certain amount of time has passed since the last speed check
        if (pros::millis() - lastCheckTime >= 500) { // Check every 200 ms
            // Check if the hook motor is going too slow
            if (hooks.get_actual_velocity() > -5 && currState != 1) {
                // Reverse the hook motor if it is going too slow
                hooks.move_velocity(600);
                pros::delay(150); // Delay to allow the motor to reverse
                hooks.move_velocity(-600); // Resume normal operation

                // Reset the timer after reversing
                lastCheckTime = pros::millis();
            } else {
                // Reset the timer if no reversal is needed
                lastCheckTime = pros::millis();
            }
        }

        pros::delay(50); // Small delay to prevent excessive CPU usage
    }
}