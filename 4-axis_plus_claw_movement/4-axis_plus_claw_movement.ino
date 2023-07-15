// Include the AccelStepper Library
#include <AccelStepper.h>

// Define pin connections
//Base
const int dirPinB = 2;
const int stepPinB = 3;

//Motor 1
const int dirPin1 = 4;
const int stepPin1 = 5;

//Motor 2
const int dirPin2 = 6;
const int stepPin2 = 7;

//Motor 3
const int dirPin3 = 8;
const int stepPin3 = 9;

//Claw
const int dirPinC = 10;
const int stepPinC = 11;


// Define motor interface type
#define motorInterfaceType 1 //type 1 is driver control

// Createing instances of motors
AccelStepper base(motorInterfaceType, stepPinB, dirPinB);
AccelStepper m1(motorInterfaceType, stepPin1, dirPin1);
AccelStepper m2(motorInterfaceType, stepPin2, dirPin2);
AccelStepper m3(motorInterfaceType, stepPin3, dirPin3);
AccelStepper claw(motorInterfaceType, stepPinC, dirPinC);

void setup() {
	// set the maximum speed, acceleration factor,
	// initial speed and the target position
	base.setMaxSpeed(1000);
	base.setAcceleration(50);
	myStepper.setSpeed(200);
	myStepper.moveTo(200);
}

void loop() {
	// Change direction once the motor reaches target position
	if (myStepper.distanceToGo() == 0) 
		myStepper.moveTo(-myStepper.currentPosition());

	// Move the motor one step
	myStepper.run();
}