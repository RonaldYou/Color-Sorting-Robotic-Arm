// Include the AccelStepper Library (https://www.pjrc.com/teensy/td_libs_AccelStepper.html)
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

  //unable to find specific from 28bjy-48 datasheet
	base.setMaxSpeed(1000);
	base.setAcceleration(50);
	base.setSpeed(200);

  m1.setMaxSpeed(1000);
	m1.setAcceleration(50);
	m1.setSpeed(200);

  m2.setMaxSpeed(1000);
	m2.setAcceleration(50);
	m2.setSpeed(200);

  m3.setMaxSpeed(1000);
	m3.setAcceleration(50);
	m3.setSpeed(200);

  claw.setMaxSpeed(1000);
	claw.setAcceleration(50);
	claw.setSpeed(200);
	
}

void loop() {
	base(1024);
}

void base(int destination){
  base.moveTo(destination);
	if(destination - base.currentPosition() > 0){
		base.move(1);
  }
  else if(destination - base.currentPosition() < 0){
    base.move(1);
  }
	base.run();
}