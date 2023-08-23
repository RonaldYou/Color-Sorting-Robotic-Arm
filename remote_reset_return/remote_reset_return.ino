#include <IRremote.h> //https://bengtmartensson.github.io/Arduino-IRremote/classIRrecv.html
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



#define motorInterfaceType 1 // Define motor interface type
#define IR_RECEIVE_PIN A5

// Createing instances of motors
AccelStepper base(motorInterfaceType, stepPinB, dirPinB);
AccelStepper m1p1(motorInterfaceType, stepPin1, dirPin1);
AccelStepper m1p2(motorInterfaceType, stepPin2, dirPin2);
AccelStepper m2(motorInterfaceType, stepPin3, dirPin3);
AccelStepper m3(motorInterfaceType, stepPin4, dirPin4);
Servo clawServo; 

//Global Variables
int servoPos = 0;
int latestCommand = 10000;

const int m1GR = 3; //gear ratios of all motors
const int m2GR = 3;
const int m3GR = 2;

const int increment = 40; //movement increment steps

int m1p1Pos = 0;
int m1p2Pos = 0;
int m2Pos = 0;
int m3Pos = 0;

void setup() {
  base.setMaxSpeed(1000);
	base.setAcceleration(50);
	base.setSpeed(100);

  m1p1.setMaxSpeed(1000);
	m1p1.setAcceleration(40);
	m1p1.setSpeed(75);

  m1p2.setMaxSpeed(1000);
	m1p2.setAcceleration(40);
	m1p2.setSpeed(75);

  m2.setMaxSpeed(1000);
	m2.setAcceleration(30);
	m2.setSpeed(75);

  m3.setMaxSpeed(1000);
	m3.setAcceleration(100);
	m3.setSpeed(100);

  clawServo.write(0); //opening claw at startup
  clawServo.attach(13);

  m1p1.setCurrentPosition(m1p1Pos);
  m1p2.setCurrentPosition(m1p2Pos);
  m2.setCurrentPosition(m2Pos);
  m3.setCurrentPosition(m3Pos);

  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
}
void loop() {
  // one revolution of stepper motor is 2048 steps (source: Ronald You)
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);
    latestCommand = IrReceiver.decodedIRData.command;
    switch (latestCommand){
      case 94: //button #3
        m3.move(m3GR * increment); m3.run(); break;
      case 90://button #6
        m3.move(m3GR * -increment); m3.run(); break;
      case 28://button #5
        m2.move(m2GR * increment); m2.run(); break;
      case 24://button #2
        m2.move(m2GR * -increment); m2.run(); break;
      case 8://button #4
        m1p1.move(m1GR * -increment); m1p2.move(m1GR * increment); m1p1.run(); m1p2.run(); break;
      case 12://button #1
        m1p1.move(m1GR * increment); m1p2.move(m1GR * -increment); m1p1.run(); m1p2.run(); break;
      case 7://button skip backward
        base.move(increment); base.run(); break;
      case 9://button skip foward
        base.move(-increment); base.run(); break; 
      case 64: // button plus sign
        //close claw
        if (servoPos == 1){
          // continue;
        } else{
          for (int pos = 0; pos <= 92; pos += 1) { //we dont need to do this, we can tell it go to end position but it moves really fast
            clawServo.write(pos);              
            delay(15);                       
          }
          servoPos = 1;
        }
        break;
      case 25: //button minus sign
        //open claw
        if(servoPos == 0){
          // continue;
        } else{
          for (int pos = 92; pos >= 0; pos -= 1) { 
            clawServo.write(pos);              
            delay(15);                       
          }
          servoPos = 0;
        }
        break;
      case 21: //button play
        //zero all motor coordinates
        m1p1Pos = 0;
        m1p2Pos = 0;
        m2Pos = 0;
        m3Pos = 0;

        m1p1.setCurrentPosition(m1p1Pos);
        m1p2.setCurrentPosition(m1p2Pos);
        m2.setCurrentPosition(m2Pos);
        m3.setCurrentPosition(m3Pos);
        break;
      case 67: //button back
        //reset all motors back to zero
        m3.moveTo(0);
        m2.moveTo(0);
        m1p1.moveTo(0);
        m1p2.moveTo(0);
        m3.run();
        m2.run();
        m1p1.run();
        m1p2.run();
        break;
    }

    IrReceiver.resume();
  }
  // clawServo.write(pos);
  runMotors();
}

void runMotors(){
  base.run();
  m1p1.run();
  m1p2.run();
  m2.run();
  m3.run();
}
