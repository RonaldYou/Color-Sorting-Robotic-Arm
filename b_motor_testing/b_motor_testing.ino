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
  base.setMaxSpeed(1000);
	base.setAcceleration(25);
	base.setSpeed(100);

  base.setCurrentPosition(0);

  Serial.begin(9600);
}

void loop() {
  if(phase == 0){
    base.moveTo(1500);
    runMotors();
    if(base.distanceToGo() == 0){
      phase = 1;
    }
    
  }
  else{           
    base.moveTo(0);
    runMotors();
  }
}

void runMotors(){
  base.run();
}
