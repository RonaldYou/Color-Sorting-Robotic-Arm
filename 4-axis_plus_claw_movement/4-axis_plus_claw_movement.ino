// Include the AccelStepper Library (https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html)
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
	base.setSpeed(100);

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
	
  base.setCurrentPosition(0);
  m1.setCurrentPosition(0);
  m2.setCurrentPosition(0);

  base.moveTo(500);
  //m1.moveTo(500);
  //m2.moveTo(500);

  Serial.begin(9600);
}

void loop() {
  
  if(base.distanceToGo() == 0){
    base.moveTo(-base.currentPosition());
    runMotors();
  }

  // if(m1.distanceToGo() == 0){
  //   m1.moveTo(0);
  //   runMotors();
  // }

  // if(m2.distanceToGo() == 0){
  //   m2.moveTo(-m2.currentPosition());
  //   runMotors();
  // }
  
  runMotors();
  
  
}

void runMotors(){
  base.run();
  m1.run();
  m2.run();
}