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
	base.setAcceleration(50);
	base.setSpeed(100);

  m1p1.setMaxSpeed(1000);
	m1p1.setAcceleration(150);
	m1p1.setSpeed(250);

  m1p2.setMaxSpeed(1000);
	m1p2.setAcceleration(150);
	m1p2.setSpeed(250);

  m2.setMaxSpeed(1000);
	m2.setAcceleration(25);
	m2.setSpeed(200);

  m3.setMaxSpeed(1000);
	m3.setAcceleration(50);
	m3.setSpeed(200);
	
  clawServo.write(0);
  clawServo.attach(13);

  //base1.setCurrentPosition(0);
  m1p1.setCurrentPosition(0);
  m1p2.setCurrentPosition(0);
  m2.setCurrentPosition(0);

  //base1.moveTo(1000);
  // m1p1.moveTo(-950);
  // m1p2.moveTo(950);
  // m2.moveTo(350);

  Serial.begin(9600);
}

void loop() {
  
  // if(base1.distanceToGo() == 0){
  //   base1.moveTo(-base1.currentPosition());
  //   runMotors();
  // }

  // if(m1p1.distanceToGo() == 0){
  //   m1p1.moveTo(-m1p1.currentPosition());
  //   runMotors();
  // }

  // if(m1p2.distanceToGo() == 0){
  //   m1p2.moveTo(-m1p2.currentPosition());
  //   runMotors();
  // }

  // if(m2.distanceToGo() == 0){
  //   m2.moveTo(-m2.currentPosition());
  //   runMotors();
  // }
  if(phase == 0){
    m1p1.moveTo(-1900);
    m1p2.moveTo(1900);
    //m2.moveTo(350);
    if(m1p1.distanceToGo() == 0){
      phase = 1;
      for (pos = 0; pos <= 92; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        clawServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
    }
    runMotors();
  }
  else{
    clawServo.write(pos);              // tell servo to go to position in variable 'pos'
    m1p1.moveTo(0);
    m1p2.moveTo(0);
    //m2.moveTo(0);
    runMotors();
  }
}

void runMotors(){
  //base.run();
  m1p1.run();
  m1p2.run();
  //m2.run();
}