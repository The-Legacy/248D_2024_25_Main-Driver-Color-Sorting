#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

bool side = false;
int wallMech = 0;
static bool toggle{false};
static bool inLifter{false};
bool toggleSorter{true};
int startTime;
bool isJamHandled = true;

// void colorSorter(){
//   while (colorSort.get_hue() >= 0 && colorSort.get_hue() <= 30 && blueSide || colorSort.get_hue() >= 300 && colorSort.get_hue() <= 360 && !blueSide) {
//     hooks.move_velocity(600);
//   }
// }

// Task colorSorting(colorSorter, "Color sorting");

// void toggleSort(){
//   if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
//     if (toggleSorter) {
//       colorSorting.suspend();
//       toggleSorter = !toggleSorter;
//     } else {
//       colorSorting.resume();
//       toggleSorter = !toggleSorter;
//     }
//   }
// }

void setIntakes() {
    // opSense.set_led_pwm(100);
    // opSense.set_integration_time(25);
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      hooks.move_velocity(600);
      preroller.move_velocity(200);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      hooks.move_velocity(-600);
      preroller.move_velocity(-200);

      // if (opSense.get_hue() < 30) {
      //   // Reverse the hook motor if it is going too slow
      //   hooks.move_velocity(600);
      //   pros::delay(150); // Delay to allow the motor to reverse
      //   hooks.move_velocity(-600); // Resume normal operation
      // }

      // pros::delay(50); // Small delay to prevent excessive CPU usage
    } else {
      hooks.move_velocity(0);
      preroller.move_velocity(0);
    }
  }


  void controlIntake() {

    // When R1 is pressed, run the intake forward
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      hooks.move(127);
      preroller.move(127);
    }
    // When L1 is pressed, run the intake backward
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        hooks.move(-127);
        preroller.move(-127);
    }
    // Otherwise, stop the intake and preroller
    else {
        hooks.brake();
        preroller.brake();
    }
  }

void setClamp() {
  if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
    if (!toggle) {
      Clamp.set_value(true);
      toggle = !toggle;
    } else {
      Clamp.set_value(false);
      toggle = !toggle;
    }
  }
}

void colorSorting(){
  opSense.set_led_pwm(100);
  opSense.set_integration_time(25);
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      hooks.move_velocity(600);
      preroller.move_velocity(200);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      if(side){
			// Run the intake motors
			hooks.move_velocity(-600);
			preroller.move_velocity(-200);

        if (opSense.get_hue() < 30 || opSense.get_hue() > 339 && currState == 0) {
          // Reverse the hook motor if it is going too slow
          hooks.move_velocity(600);
          pros::delay(150); // Delay to allow the motor to reverse
          hooks.move_velocity(-600); // Resume normal operation
        }

			pros::delay(50); // Small delay to prevent excessive CPU usage
	  } else{
			// Run the intake motors
			hooks.move_velocity(-600);
			preroller.move_velocity(-200);

			if (opSense.get_hue() > 200 && opSense.get_hue() < 340 && currState == 0) {
				// Reverse the hook motor if it is going too slow
				hooks.move_velocity(600);
				pros::delay(150); // Delay to allow the motor to reverse
				hooks.move_velocity(-600); // Resume normal operation
			}

			pros::delay(50); // Small delay to prevent excessive CPU usage
	  }
    } else {
      hooks.move_velocity(0);
      preroller.move_velocity(0);
    }
}

void setLifter() {
  if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
    if(!inLifter) {
      inLift.set_value(true);
      inLifter = !inLifter;
    } else {
      inLift.set_value(false);
      inLifter = !inLifter;
    }
  }
}

void setLB(){
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
    nextState();
  } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
    if(currState == 4){
      currState = 0;
    } else {
      currState = 4;
      target = states[currState];
    }
  } else if (currState == 1 && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
    currState = 0;
    target = states[currState];
  } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    currState = 1;
    target = states[currState];
  }
}

void ledTime() {
  driverClock.start();
  driverClock.waitUntil(30 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(29 * 1000);
  TimeLED.off();
  driverClock.waitUntil(38 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(27 * 1000);
  TimeLED.off();
  driverClock.waitUntil(26 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(25 * 1000);
  TimeLED.off();
  driverClock.waitUntil(24 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(23 * 1000);
  TimeLED.off();
  driverClock.waitUntil(22 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(21 * 1000);
  TimeLED.off();
  driverClock.waitUntil(20 * 1000);
  TimeLED.flow(0x4B0082, 0xD9AEFF);
  driverClock.waitUntil(19 * 1000);
  TimeLED.off();
  driverClock.waitUntil(18 * 1000);
  TimeLED.setColor(0xE5195E);
  driverClock.waitUntil(.2 * 1000);
  Clamp.set_value(LOW);
}