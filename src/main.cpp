#include "main.h"
#include "pros/rtos.h"
#include "robodash/api.h"

rd::Selector Match_autos({
	{"State Skills", &stateSkills},
	{"Wallstake Rush Blue", &WallstakeRush_Blue},
	{"Safe Red Goal", &goalSideSafeRed},
	{"Red Sig AWP", &redWP_yippie},
	{"Blue Sig AWP", &blueWP_yippie},	
	{"Safe Blue Goal", &goalSideSafeBlue},
	{"State Blue Goal Rush", &stateBlueGoalRush},
	{"State Red Goal Rush", &stateRedGoalRush},
	{"Wallstake Rush Red", &WallstakeRush_Red},
	{"Lame Blue Duck", &lameBlueDuck},
	{"Lame Red Duck", &lameRedDuck},
	{"Blue Solo Winpoint", &blueSoloWP},
	{"Blue Pause", &blueSoloPause},
	{"Red goal rush", &redGoalRush},
	{"Blue elims rush", &blueElimsRush},
	{"Blue goal rush", &blueGoalRush},
	{"Red Four Donut", &redFourDonut},
	{"Blue Four Donut", &blueFourDonut},
	{"Skills Yolo", &skillsYolo},
	{"Red Solo Winpoint", &redSoloWP},
});

void initialize() {
	Match_autos.focus();
	console.println("Initializing robot...");
	chassis.calibrate(); // calibrate sensors
	ledManager.initialize(); // initialize the LED manager
	ledManager.flow(0x421C52, 0x732C7B);
	pros::Task liftControlTask(LBTask, "LB Task");
	pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            console.printf("X: %f", chassis.getPose().x); // x
            console.printf("Y: %f", chassis.getPose().y); // y
            console.printf("Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(50);
			console.clear();
        }
    });
}

void disabled() {
	
}

void competition_initialize() {
  
}

void autonomous() {
	console.println("Running auton...");
	console.focus();
	Match_autos.run_auton();
	
}

void opcontrol() {
	console.clear();
	console.println("Driving...");
	currState = 0;
	target = states[currState];
	while (true) {
		// get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX, false, 0.5);
		
		// set subsystems
		colorSorting();
		setLifter();
		setClamp();
		setLB();
		
		pros::delay(10);          // Run for 10 ms then update
	}
}