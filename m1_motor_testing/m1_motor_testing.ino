// Include the AccelStepper Library (https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html)
#include <AccelStepper.h>
#include <Servo.h>

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
const int dirPin4 = 10;
const int stepPin4 = 11;


// Define motor interface type
#define motorInterfaceType 1 //type 1 is driver control

// Createing instances of motors
AccelStepper base(motorInterfaceType, stepPinB, dirPinB);
AccelStepper m1p1(motorInterfaceType, stepPin1, dirPin1);
AccelStepper m1p2(motorInterfaceType, stepPin2, dirPin2);
AccelStepper m2(motorInterfaceType, stepPin3, dirPin3);
AccelStepper m3(motorInterfaceType, stepPin4, dirPin4);


Servo clawServo; 
int pos = 0;
int phase = 0;


void setup() {

  //unable to find specific from 28bjy-48 datasheet

  m1p1.setMaxSpeed(1000);
	m1p1.setAcceleration(150);
	m1p1.setSpeed(100);

  m1p2.setMaxSpeed(1000);
	m1p2.setAcceleration(150);
	m1p2.setSpeed(100);

	

  //base1.setCurrentPosition(0);
  m1p1.setCurrentPosition(0);
  m1p2.setCurrentPosition(0);
  //m2.setCurrentPosition(0);

  //base1.moveTo(1000);
  m1p1.moveTo(-1650);
  m1p2.moveTo(1650);
  // m2.moveTo(350);

  Serial.begin(9600);
}

void loop() {
  
  if(m1p1.distanceToGo() == 0){
    m1p1.moveTo(-m1p1.currentPosition());
    runMotors();
  }

  if(m1p2.distanceToGo() == 0){
    m1p2.moveTo(-m1p2.currentPosition());
    runMotors();
  }

  runMotors();

  // if(phase == 0){
  //   m1p1.moveTo(-950);
  //   runMotors();
  //   m1p2.moveTo(950);
  //   runMotors();
  //   if(m1p1.distanceToGo() == 0){
  //     phase = 1;
  //   }
    
  // }
  // else{           
  //   m1p1.moveTo(0);
  //   runMotors();
  //   m1p2.moveTo(0);
  //   runMotors();
  // }
}

void runMotors(){
  //base.run();
  m1p1.run();
  m1p2.run();
  //m2.run();
}
