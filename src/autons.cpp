#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/rtos.hpp"

//gloabl bool
extern bool side;

//Assets
ASSET(SkillsP1_txt)
ASSET(SkillsP2_txt)

void moveRelative(float distance, float maxSpeed, int timeout) {
    double headingRadians = chassis.getPose(true).theta;
    double startingX = chassis.getPose().x;
    double startingY = chassis.getPose().y;
    double deltaX = distance * sin(headingRadians);
    double deltaY = distance * cos(headingRadians);
    double newX = startingX + deltaX;
    double newY = startingY + deltaY;
    if (distance > 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxSpeed});
    }
    else if (distance < 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxSpeed});
    }
};

void redSoloWP(){
    side = false;
    Clamp.set_value(LOW);
    chassis.setPose(0, 0, 323);
    pros::delay(2500);
    chassis.moveToPose(-7.5, 9.5, 323, 2000, {.maxSpeed = 110, .minSpeed = 60});
    chassis.waitUntil(7);
    currState = 3;
    target = states[currState];
    pros::delay(1250);
    currState = 0;
    target = states[currState];
    chassis.moveToPose(20.5, -30, 323, 2500, {.forwards=false, .maxSpeed = 90, .minSpeed = 60}, false);
    pros::delay(750);
    Clamp.set_value(HIGH);
    pros::delay(250);
    intake.move(-127);
    chassis.turnToPoint(48, -25.5, 1000);
    chassis.moveToPose(48, -25.5, 110, 1500, {.maxSpeed = 110, .minSpeed = 60});
    pros::delay(750);
    chassis.turnToPoint(42, -39, 1000);
    chassis.moveToPoint(42, -39, 1500, {.maxSpeed = 110, .minSpeed = 60});
    pros::delay(750);
    chassis.moveToPoint(53, 0, 2000, {.forwards=false, .maxSpeed = 110, .minSpeed = 60});
    //chassis.moveToPose(-10, -30, 270, 4000, {.maxSpeed = 60, .minSpeed = 50});
}

void blueSoloWP(){
    side = true;
    Clamp.set_value(LOW);
    chassis.setPose(0, 0, 37);
    chassis.moveToPose(7.5, 9.5, 37, 2000, {.maxSpeed = 110, .minSpeed = 60});
    chassis.waitUntil(7);
    currState = 3;
    target = states[currState];
    pros::delay(1250);
    currState = 0;
    target = states[currState];
    chassis.moveToPose(-17, -31, 37, 2500, {.forwards=false, .maxSpeed = 60, .minSpeed = 50}, false);
    pros::delay(750);
    Clamp.set_value(HIGH);
    pros::delay(250);
    intake.move(-127);
    chassis.turnToPoint(-40, -22.5, 1000);
    chassis.moveToPose(-40, -22.5, 110, 1500, {.maxSpeed = 110, .minSpeed = 60});
    pros::delay(750);
    chassis.turnToPoint(-44, -36, 1000);
    chassis.moveToPoint(-44, -36, 1500, {.maxSpeed = 110, .minSpeed = 60});
    pros::delay(750);
    //chassis.moveToPoint(-54, 0, 2000, {.forwards=false, .maxSpeed = 110, .minSpeed = 60});
    chassis.moveToPose(-30, -22.5, 270, 4000, {.forwards=false, .maxSpeed = 60, .minSpeed = 50});
}

void blueSoloPause(){
    side = true;
    Clamp.set_value(LOW);
    chassis.setPose(0, 0, 37);
    pros::delay(2500);
    chassis.moveToPose(7.5, 9.5, 37, 2000, {.maxSpeed = 110, .minSpeed = 60});
    chassis.waitUntil(7);
    currState = 3;
    target = states[currState];
    pros::delay(1250);
    currState = 0;
    target = states[currState];
    chassis.moveToPose(-17, -31, 37, 2500, {.forwards=false, .maxSpeed = 60, .minSpeed = 50}, false);
    pros::delay(750);
    Clamp.set_value(HIGH);
    pros::delay(250);
    intake.move(-127);
    chassis.turnToPoint(-40, -22.5, 1000);
    chassis.moveToPose(-40, -22.5, 110, 1500, {.maxSpeed = 110, .minSpeed = 60});
    pros::delay(750);
    chassis.turnToPoint(-44, -36, 1000);
    chassis.moveToPoint(-44, -36, 1500, {.maxSpeed = 110, .minSpeed = 60});
    pros::delay(750);
    //chassis.moveToPoint(-54, 0, 2000, {.forwards=false, .maxSpeed = 110, .minSpeed = 60});
    chassis.moveToPose(-30, -22.5, 270, 4000, {.forwards=false, .maxSpeed = 60, .minSpeed = 50});
}

void redGoalRush(){
    side = false;
    chassis.setPose(-58.367, -35.377,90);
    preroller.move(0);
    chassis.moveToPoint(-15.629, -50.226, 1500, {.maxSpeed=100, .minSpeed=60}, false);
    inLift.set_value(HIGH);
    pros::delay(750);
    chassis.moveToPose(-27.092, -41.801, 180, 1500, {.forwards=false, .maxSpeed=100, .minSpeed=60}, false);
    chassis.turnToPoint(27.491, -80, 1000);
    inLift.set_value(LOW);
    chassis.turnToPoint(-27, -50, 1000, {.maxSpeed=90}, false);
    chassis.moveToPoint(-27.631, -23.491, 2000, {.forwards=false, .maxSpeed=85, .minSpeed=60}, false);
    Clamp.set_value(HIGH);
    pros::delay(1500);
    intake.move(-127);
    preroller.move(-127);
    pros::delay(1000);
    chassis.moveToPoint(-22, 0, 3000, {.maxSpeed=60, .minSpeed=40});
}

void blueGoalRush(){
    side = true;
    chassis.setPose(44.765, -59.842,270);
    preroller.move(-127);
    chassis.moveToPoint(16.028, -54.571, 1500, {.maxSpeed=90, .minSpeed=60}, false);
    inLift.set_value(HIGH);
    pros::delay(250);
    chassis.moveToPose(20.491, -51.186, 180, 1000, {.forwards=false, .maxSpeed=90, .minSpeed=60}, false);
    inLift.set_value(LOW);
    chassis.turnToPoint(14.491, -80, 1000);
    chassis.moveToPoint(14.491, -24.299, 1500, {.forwards=false, .maxSpeed=60, .minSpeed=50}, false);
    pros::delay(500);
    Clamp.set_value(HIGH);
    pros::delay(500);
    intake.move(-127);
    chassis.moveToPoint(21.527, -.299, 3000, {.maxSpeed=60, .minSpeed=40});
}

void blueElimsRush(){
    side = true;
    chassis.setPose(44.765, -59.842,290);
    preroller.move(-127);
    chassis.moveToPoint(15.028, -51.571, 1500, {.maxSpeed=90, .minSpeed=60}, false);
    inLift.set_value(HIGH);
    pros::delay(150);
    chassis.moveToPose(28.491, -50.186, 180, 1500, {.forwards=false, .maxSpeed=90, .minSpeed=60}, false);
    inLift.set_value(LOW);
    pros::delay(500);
    chassis.turnToPoint(14.491, -80, 1000);
    chassis.moveToPoint(14.491, -25.299, 1500, {.forwards=false, .maxSpeed=60, .minSpeed=50}, false);
    pros::delay(250);
    Clamp.set_value(HIGH);
    pros::delay(250);
    intake.move(-127);
    pros::delay(1000);
    Clamp.set_value(LOW);
    chassis.turnToPoint(13, 53, 1000);
    chassis.moveToPoint(13, -53, 1500, {.forwards=false, .maxSpeed=65, .minSpeed=50}, false);
    pros:delay(150);
    Clamp.set_value(HIGH);
    pros::delay(150);
    chassis.turnToPoint(44, -63, 1000);
}

void redFourDonut(){
    side = false;
    chassis.setPose(-59.713, 23.362, 270);
    chassis.moveToPoint(-23.362, 23.092, 1500, {.forwards=false, .maxSpeed=85, .minSpeed=60});
    inLift.set_value(HIGH);
    pros::delay(750);
    intake.move(-127);
    chassis.moveToPose(-5.59, 40.056, 0, 1500, {.maxSpeed=85, .minSpeed=65});
    chassis.moveToPoint(-5.859, 58.251, 1500, {.maxSpeed=90, .minSpeed=65});
    pros::delay(750);
    chassis.moveToPoint(-23.092, 48.134, 1500);
    pros::delay(750);
    chassis.moveToPoint(-24.439, 1.551, 2500, {.maxSpeed=55, .minSpeed=40});
}

void blueFourDonut(){
    side = true;
    chassis.setPose(58.765, 23.631, 90);
    chassis.moveToPoint(29.684, 24.17, 1500, {.forwards=false, .maxSpeed=85, .minSpeed=60});
    inLift.set_value(HIGH);
    pros::delay(750);
    intake.move(-127);
    chassis.moveToPose(7.335, 36.287, 0, 1500, {.maxSpeed=85, .minSpeed=65});
    chassis.moveToPoint(7.066, 55.943, 1500, {.maxSpeed=90, .minSpeed=65});
    pros::delay(750);
    chassis.moveToPoint(24.299, 46.519, 1500);
    pros::delay(750);
    chassis.moveToPoint(23.222, 2.359, 2500, {.maxSpeed=55, .minSpeed=40});
}

void rushRed(){
    side = false;
    chassis.setPose(51, -60,90);
    chassis.moveToPoint(15, -60, 1250, {.forwards = false});
    chassis.turnToPoint(8.61, -53.904, 1000);
    chassis.moveToPoint(8.61, -53.904, 1000);
}

void rushBlue(){
    side = true;
    chassis.setPose(51, -60,90);
    chassis.moveToPoint(15, -60, 1100, {.forwards = false});
    chassis.turnToPoint(8.61, -55, 650, {.forwards = false});
    chassis.moveToPoint(6, -53, 1000, {.forwards = false, .maxSpeed = 80}, false);
    // Clamp.set_value(HIGH);
    // intake.move(127);
    // pros::delay(100);
    // chassis.swingToPoint(25.42, -41.763, lemlib::DriveSide::LEFT, 1000);
}

void skills(){
    side = false;
    chassis.setPose(0, 0,30);
    currState = 3;
    target = states[currState];
    pros::delay(750);
    currState = 2;
    target = states[currState];
    chassis.moveToPoint(-16, -12, 1100, {.forwards = false, .maxSpeed=50}, false);
    pros::delay(250);
    Clamp.set_value(HIGH);
    pros::delay(250);
    chassis.turnToPoint(-20, -36, 1000);
    intake.move(-127);
    chassis.moveToPoint(-20, -34, 1250, {.maxSpeed=80, .minSpeed=70});
    // chassis.turnToPoint(-46, -86, 1500, {.maxSpeed=80, .minSpeed=70});
    // chassis.moveToPoint(-40, -86, 1500, {.maxSpeed=80, .minSpeed=70}, false);
    //pros::delay(1750);
    //chassis.moveToPoint(-46, -109, 1000, {.maxSpeed=80, .minSpeed=70}, false);

    //wall stake
    // currState = 1;
    // target = states[currState];
    // pros::delay(500);
    // chassis.moveToPoint(-40, -70, 1500, {.forwards=false, .maxSpeed=70, .minSpeed=60}, false);
    chassis.turnToPoint(-82, -84, 1000);
    chassis.moveToPoint(-82, -84, 1000, {.maxSpeed=80}, false);
    // intake.move(0);
    // currState = 3;
    // target = states[currState];
    // pros::delay(1000);
    // intake.move(-127);
    // currState = 2;
    // target = states[currState];
    // pros::delay(750);

    //other four
    //chassis.moveToPoint(-47, -70, 1500, {.forwards=false, .maxSpeed=80, .minSpeed=60}, false);
    chassis.turnToPoint(-44, -20, 1000);
    chassis.moveToPoint(-44, 0, 1500, {.maxSpeed=65, .minSpeed=50}, false);
    chassis.moveToPoint(-30, -12, 1500, {.forwards=false, .maxSpeed=80});
    chassis.moveToPoint(-53, -12, 1500, {.maxSpeed=80});
    chassis.turnToPoint(0, -100, 1000);
    chassis.moveToPoint(-60, 0, 1000, {.forwards=false, .maxSpeed=90});
    Clamp.set_value(LOW);
    currState = 0;
    target = states[currState];
    intake.move(0);
    chassis.moveToPoint(-53, -20, 1000, {.maxSpeed=90});
    
    //second goal
    chassis.moveToPoint(20, -5, 2500, {.forwards=false, .maxSpeed=60}, false);
    pros::delay(250);
    Clamp.set_value(HIGH);
    intake.move(-127);

    //first second donut
    chassis.turnToPoint(30, -28, 1000);
    chassis.moveToPoint(30, -28, 1500, {.maxSpeed=85});

    //second second
    chassis.turnToPoint(63, -50, 1000);
    chassis.moveToPoint(63, -50, 1000, {.maxSpeed=85});

    //other four
    chassis.turnToPoint(49, -30, 1000);
    chassis.moveToPoint(49, -30, 1500, {.maxSpeed=85});
    chassis.turnToPoint(49, 0, 1000);
    chassis.moveToPoint(49, 0, 1500, {.maxSpeed=65});
    chassis.moveToPoint(35, -2, 1000, {.forwards=false, .maxSpeed=85});
    chassis.moveToPoint(60, -2, 1500,{.maxSpeed=85});
    chassis.turnToPoint(0, -100, 1000);
    chassis.moveToPoint(65, 8, 1000, {.forwards=false, .maxSpeed=85});
    Clamp.set_value(LOW);
    chassis.moveToPoint(-38, -99, 3500, {.maxSpeed=90});
    chassis.waitUntil(80);
    intake.move(0);
    chassis.turnToPoint(-82, -84, 1000);
    chassis.moveToPoint(65, -115, 5000, {.forwards=false, .maxSpeed=85}, false);
    chassis.moveToPoint(-65, -115, 5000);
    // Clamp.set_value(HIGH);
    // chassis.moveToPoint(-40, -120, 1500, {.maxSpeed=85});
    // intake.move(-127);
}

void skillsYolo(){
    side = false;
    //allience stake
    chassis.setPose(-61.059, -6.258,270);
    currState = 3;
    target = states[currState];
    pros::delay(750);
    currState = 2;
    target = states[currState];

    //goal + first donut
    chassis.moveToPoint(-46.788, -23.222, 1500, {.forwards=false, .maxSpeed=60, .minSpeed=50}, false);
    Clamp.set_value(HIGH);
    pros::delay(750);
    intake.move(-127);
    chassis.moveToPoint(-23.631, -24.029, 1500, {.maxSpeed=90, .minSpeed=60});

    //second donut
    chassis.moveToPoint(0.334, -59.438, 1500, {.maxSpeed=90, .minSpeed=60});
    pros::delay(750);
    chassis.moveToPoint(0.334, -43.438, 1500, {.forwards=false, .maxSpeed=90, .minSpeed=60});

    //other three
    chassis.moveToPoint(-23.092, -46.648, 1500, {.maxSpeed=90, .minSpeed=60});
    chassis.turnToPoint(-59.174, -45.706, 1000);
    chassis.moveToPoint(-59.174, -45.706, 1500, {.maxSpeed=90, .minSpeed=60});

    //last
    chassis.turnToPoint(-47.327, -59.304, 1000);
    chassis.moveToPoint(-47.327, -59.304, 1500, {.maxSpeed=90, .minSpeed=60});
    chassis.moveToPoint(-59.04, -63.208, 1500, {.forwards=false, .maxSpeed=90, .minSpeed=60});
    Clamp.set_value(LOW);
    intake.move(0);
    currState = 0;
    target = states[currState];

    //second goal
    chassis.moveToPoint(-47.327, -59.304, 1500, {.maxSpeed=90, .minSpeed=60});
    chassis.moveToPoint(-47.192, 23.015, 1500, {.forwards=false, .maxSpeed=60, .minSpeed=50}, false);
    Clamp.set_value(HIGH);
    pros::delay(750);
    intake.move(-127);

    //first on second goal
    chassis.moveToPoint(-24.035, 23.496, 1500, {.maxSpeed=90, .minSpeed=60});

    //second on second goal
    chassis.moveToPoint(0.199, 59.04, 1500, {.maxSpeed=90, .minSpeed=60});
    pros::delay(750);
    chassis.moveToPoint(0.199, 46.04, 1500, {.forwards=false, .maxSpeed=90, .minSpeed=60});

    //third fourth and fifth
    chassis.moveToPoint(-23.496, 47.192, 1500, {.maxSpeed=90, .minSpeed=60});
    chassis.turnToPoint(-62.675, 48.404, 1500, {.maxSpeed=90, .minSpeed=60});
    chassis.moveToPoint(-62.675, 48.404, 1500, {.maxSpeed=90, .minSpeed=60});

    //second last
    chassis.moveToPoint(-44.634, 58.636, 1500, {.maxSpeed=90, .minSpeed=60});
    chassis.moveToPoint(-57.693, 62.81, 1500, {.forwards=false, .maxSpeed=90, .minSpeed=60});
    Clamp.set_value(LOW);
    intake.move(0);

    //Third Goal
    chassis.moveToPoint(22.818, -24.433, 4000, {.maxSpeed=90, .minSpeed=60});
    chassis.waitUntil(80);
    intake.move(-127);
    chassis.moveToPose(38.166, -24.164, 180, 1500, {.maxSpeed=90, .minSpeed=60});
    intake.move(0);
    chassis.moveToPoint(46.917, 0.205, 1500, {.forwards=false, .maxSpeed=60, .minSpeed=50}, false);
    Clamp.set_value(HIGH);
    pros::delay(750);

    //third first
    chassis.moveToPoint(23.491, -46.917, 1500, {.maxSpeed=90, .minSpeed=60});
    intake.move(-127);
    pros::delay(750);
    chassis.moveToPoint(47.994, -46.379, 1500, {.maxSpeed=90, .minSpeed=60});
    
    //third corner
    chassis.moveToPoint(62.842, -62.034, 1500, {.forwards=false, .maxSpeed=90, .minSpeed=60});
    Clamp.set_value(LOW);

    //last corner
    chassis.moveToPoint(43.148, -22.683, 1500, {.maxSpeed=90, .minSpeed=60});
    chassis.moveToPoint(55.803, 3.705, 2000, {.maxSpeed=90, .minSpeed=60});
    chassis.moveToPoint(64.42, 64.423, 2000, {.maxSpeed=90, .minSpeed=60});
}

void redWP_yippie(){
    side = false;
    chassis.setPose(-55.035, 6.817, 220);
    chassis.moveToPose(-61.5, -0.5, 220, 1000, {.maxSpeed=90, .minSpeed= 60}, false);
    //alliance stakes
    currState = 3;
    target = states[currState];
    pros::delay(750);
    currState = 0;
    target = states[currState];
    chassis.moveToPoint(-25, 28, 1500, {.forwards=false, .maxSpeed=70, .minSpeed=50}, false);
    pros::delay(150);
    Clamp.set_value(HIGH);
    pros::delay(150);
    chassis.turnToPoint(-28, 52, 1000);
    chassis.moveToPoint(-28, 52, 1500, {.maxSpeed = 90, .minSpeed = 60});
    intake.move(-127);
    pros::delay(150);
    chassis.moveToPoint(-42, 35, 2000,{.maxSpeed = 90, .minSpeed = 60}, false);
    chassis.turnToPoint(-42, 0, 1000);
    Clamp.set_value(LOW);
    chassis.moveToPoint(-42, -30, 2500,{.maxSpeed = 70, .minSpeed = 60}, false);
    intake.move(0);
    chassis.turnToPoint(-40.144, -40.073, 1000);
    chassis.moveToPoint(-21.144, -25.073, 1500, {.forwards=false, .maxSpeed = 65, .minSpeed = 50},false);
    pros::delay(150);
    Clamp.set_value(HIGH);
    intake.move(-127);
    chassis.turnToPoint(-14, -50, 1500);
    chassis.moveToPoint(-14, -50, 1500);
    chassis.turnToPoint(-20, 0, 1000);
    chassis.moveToPoint(-20, 0, 2000,{.maxSpeed = 70, .minSpeed = 40});
    }

    void blueWP_yippie(){
        side = true;
        chassis.setPose(55.035, 6.817, 140);
        chassis.moveToPose(58.5, -3, 220, 1000, {.maxSpeed=90, .minSpeed= 60}, false);
        //alliance stakes
        currState = 3;
        target = states[currState];
        pros::delay(750);
        currState = 0;
        target = states[currState];
        chassis.moveToPoint(25, 28, 1500, {.forwards=false, .maxSpeed=70, .minSpeed=50}, false);
        pros::delay(150);
        Clamp.set_value(HIGH);
        pros::delay(150);
        chassis.turnToPoint(28, 52, 1000);
        chassis.moveToPoint(28, 52, 1500, {.maxSpeed = 90, .minSpeed = 60});
        intake.move(-127);
        pros::delay(150);
        chassis.moveToPoint(42, 35, 2000,{.maxSpeed = 90, .minSpeed = 60}, false);
        chassis.turnToPoint(46, 0, 1000);
        Clamp.set_value(LOW);
        chassis.moveToPoint(46, -35, 2500,{.maxSpeed = 70, .minSpeed = 60});
        chassis.waitUntil(55);
        intake.move(0);
        chassis.turnToPoint(70.144, -70.073, 1000);
        chassis.moveToPoint(21.144, -25.073, 1500, {.forwards=false, .maxSpeed = 60, .minSpeed = 50},false);
        pros::delay(150);
        Clamp.set_value(HIGH);
        intake.move(-127);
        chassis.turnToPoint(14, -46, 1500);
        chassis.moveToPoint(14, -46, 1500);
        chassis.turnToPoint(20, 0, 1000);
        chassis.moveToPoint(20, 0, 2000,{.maxSpeed = 70, .minSpeed = 40});
    }

    void stateSkills(){
        pros::Task antiJam(intakeTask);
        antiJam.suspend();
        intake.move(0);
        side = false;
        chassis.setPose(-52.443, -0.603, 270);
        //allience stake
        currState = 4;
        target = states[currState] - 510;
        pros::delay(750);
        chassis.moveToPoint(-47, 0, 1500, {.forwards=false, .maxSpeed=90, .minSpeed=60}, false);
        currState = 0; 
        target = states[currState] - 510;
        //grab goal
        chassis.turnToPoint(-47.713, 20.784, 1000);
        chassis.moveToPoint(-45.057, -20.798, 1500, {.forwards=false, .maxSpeed=60, .minSpeed=50}, false);
        pros::delay(150);
        Clamp.set_value(HIGH);
        pros::delay(150);
        //donut
        chassis.turnToPoint(-23.631, -27.568, 1000, {}, false);
            //intake.move(-127);
            antiJam.resume();
        chassis.moveToPoint(-23.631, -27.568, 1500, {.maxSpeed=100, .minSpeed=60});
        chassis.turnToPoint(-13.399, -52.303, 1000);
        chassis.moveToPoint(26.222, -50.917, 2000, {.maxSpeed=100, .minSpeed=60});
        //wall stake
        chassis.turnToPoint(12, -59.496, 1000);
        chassis.moveToPoint(12, -59.5, 1500, {.maxSpeed=100, .minSpeed=60}, false);
        currState = 1; 
        target = states[currState] - 505;
        chassis.turnToPoint(6, -70, 1000);
        chassis.moveToPoint(6, -70, 1000, {}, false);
        pros::delay(500);
            antiJam.suspend();
            intake.move(0);
        currState = 3; 
        target = states[currState] - 510;
        pros::delay(750);
        currState = 0; 
        target = states[currState] - 510;
        pros::delay(250);
        //otehr donuts
        chassis.turnToPoint(-24.17, -50.648, 1000);
        chassis.moveToPoint(-24.17, -50.648, 1500, {.maxSpeed=100, .minSpeed=60});
            //intake.move(-127);
            antiJam.resume();
        chassis.moveToPoint(-59.982, -50.994, 2500, {.maxSpeed=70, .minSpeed=50});
        chassis.turnToPoint(-47.327, -59.304, 1000);
        chassis.moveToPoint(-47.327, -59.304, 1500, {.maxSpeed=100, .minSpeed=60});
        chassis.turnToPoint(-5.859, -39.109, 1000, {}, false);
        Clamp.set_value(LOW);
        chassis.moveToPoint(-59.982, -64.15, 1500, {.forwards=false, .maxSpeed=100, .minSpeed=60}, false);
            antiJam.suspend();
            intake.move(0);
        //second goal
        chassis.moveToPoint(-48.788, -48.533, 1500, {.maxSpeed=100, .minSpeed=60});
        chassis.turnToPoint(-48.788, -60, 1000);
        chassis.moveToPoint(-48.057, 22.015, 2500, {.forwards=false, .maxSpeed=60, .minSpeed=50}, false);
        pros::delay(150);
        Clamp.set_value(HIGH);
        pros::delay(150);
        //second goal donuts
            //intake.move(-127);
            antiJam.resume();
        chassis.turnToPoint(-22.554, 23.631, 1000);
        chassis.moveToPoint(-22.554, 23.631, 1500, {.maxSpeed=100, .minSpeed=70});
        chassis.turnToPoint(-21.708, 46.788, 1000);
        chassis.moveToPoint(-21.708, 46.788, 1500, {.maxSpeed=100, .minSpeed=70});
        chassis.turnToPoint(-59.444, 47.596, 1000);
        chassis.moveToPoint(-59.444, 47.596, 2000, {.maxSpeed=70, .minSpeed=70});
        chassis.turnToPoint(-47.596, 58.636, 1000);
        chassis.moveToPoint(-47.865, 58.636, 1500, {.maxSpeed=100, .minSpeed=70});
        chassis.moveToPoint(-62, 62, 1500, {.forwards=false, .maxSpeed=100, .minSpeed=70}, false);
        pros::delay(750);
        Clamp.set_value(LOW);
            antiJam.suspend();
            intake.move(0);
        //second wallstake
        currState = 1; 
        target = states[currState] - 505;
        chassis.moveToPoint(-2, 62.713, 2000, {.maxSpeed=100, .minSpeed=60});
        chassis.waitUntil(20);
            //intake.move(-127);
            antiJam.resume();
        chassis.turnToPoint(5, 70, 1000);
        chassis.moveToPoint(5, 70, 1000, {.maxSpeed=100, .minSpeed=60}, false);
        pros::delay(500);
            antiJam.suspend();
            intake.move(0);
        pros::delay(250);
        currState = 3; 
        target = states[currState] - 510;
        pros::delay(750);
        currState = 0; 
        target = states[currState] - 510;
        pros::delay(500);
        chassis.moveToPoint(6, 65, 1500, {.forwards=false, .maxSpeed=100, .minSpeed=60});

        //third goal
        chassis.turnToPoint(28.837, 28.477, 1000);
            //intake.move(-127);
            antiJam.resume();
        chassis.moveToPoint(28.837, 24.477, 1500, {.maxSpeed=100, .minSpeed=60}, false);
            antiJam.suspend();
            intake.move(0);
        chassis.turnToPoint(-25, 70, 1000);
        chassis.moveToPoint(58.725, 0, 1500, {.forwards=false, .maxSpeed=65, .minSpeed=50}, false);
        Clamp.set_value(HIGH);
            //intake.move(-127);
            antiJam.resume();

        //more donits
        chassis.moveToPoint(31.299, 52.596, 1500, {.maxSpeed=100, .minSpeed=80});
        chassis.turnToPoint(60, 52.596, 1000);
        chassis.moveToPoint(53, 53, 1500, {.maxSpeed=100, .minSpeed=80});
        chassis.turnToPoint(62, 67, 1000);
        chassis.moveToPoint(62, 65, 1500, {.maxSpeed=100, .minSpeed=80});
        chassis.turnToPoint(-9.22, -38.171, 1000, {}, false);
        Clamp.set_value(LOW);
        chassis.moveToPoint(65.266, 68.982, 2100, {.forwards=false, .maxSpeed=100, .minSpeed=60}, false);
            antiJam.suspend();
            intake.move(0);
        //last corner
        chassis.moveToPose(55.301, 16.63, 160, 2000, {.maxSpeed=100, .minSpeed=80});
        chassis.moveToPoint(76.305, -56.342, 2000, {.maxSpeed=100, .minSpeed=80});

        //last allience stake
        chassis.moveToPoint(59.342, -24.338, 1500, {.forwards=false, .maxSpeed=100, .minSpeed=60}, false);
            //intake.move(-127);
            antiJam.resume();
        currState = 1; 
        target = states[currState] - 510;
        chassis.moveToPoint(55.917, -42.264, 1500, {.maxSpeed=100, .minSpeed=60});
        chassis.turnToPoint(67.266, -10.912, 1000);
        chassis.moveToPoint(67.266, -8.912, 1500, {.maxSpeed=100, .minSpeed=60}, false);
        chassis.turnToPoint(82.5, 0, 1000);
        currState = 4; 
        target = states[currState] - 510;
        antiJam.suspend();
        intake.move(0);
    }