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
	m1p1.setAcceleration(25);
	m1p1.setSpeed(75);

  m1p2.setMaxSpeed(1000);
	m1p2.setAcceleration(25);
	m1p2.setSpeed(75);

  m2.setMaxSpeed(1000);
	m2.setAcceleration(25);
	m2.setSpeed(50);

  m3.setMaxSpeed(1000);
	m3.setAcceleration(25);
	m3.setSpeed(75);
	
  clawServo.write(0);
  clawServo.attach(13);

  base.setCurrentPosition(0);
  m1p1.setCurrentPosition(0);
  m1p2.setCurrentPosition(0);
  m2.setCurrentPosition(0);
  m3.setCurrentPosition(0);

  Serial.begin(9600);
}

void loop() {
  if(phase == 0){
    m1p1.moveTo(-1650);
    m1p2.moveTo(1650);
    m2.moveTo(1200);
    m3.moveTo(1700);
    if(m1p1.distanceToGo() == 0 && m1p2.distanceToGo() == 0 && m2.distanceToGo() == 0){
      phase = 1;
      for (pos = 0; pos <= 92; pos += 1) { // goes from 0 degrees to 180 degrees
        clawServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
    }
    runMotors();
  }
  else if(phase == 1){
    clawServo.write(pos);             
    m1p1.moveTo(-1350);
    m1p2.moveTo(1350);
    base.moveTo(500);
    if(m1p1.distanceToGo() == 0 && base.distanceToGo() = 0){
      phase = 2;
    }
    runMotors();
  }
  else if(phase == 2){
    clawServo.write(pos);
    m1p1.moveTo(-1650);
    m1p2.moveTo(1650);
    if(m1p1.distanceToGo() == 0 && m1p2.distanceToGo() == 0){
      phase = 3;
      for (pos = 92; pos => 0; pos--) { // goes from 0 degrees to 180 degrees
        clawServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
    }
    runMotors();
  }

}

void runMotors(){
  base.run();
  m1p1.run();
  m1p2.run();
  m2.run();
  m3.run();
}