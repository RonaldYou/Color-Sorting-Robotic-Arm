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
int pos = 0;
int latestCommand = 10000;


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
	m2.setAcceleration(50);
	m2.setSpeed(75);

  m3.setMaxSpeed(1000);
	m3.setAcceleration(100);
	m3.setSpeed(100);

  clawServo.write(0);
  clawServo.attach(13);

  m1p1.setCurrentPosition(0);
  m1p2.setCurrentPosition(0);
  m2.setCurrentPosition(0);
  m3.setCurrentPosition(0);

  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
}
void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);
    latestCommand = IrReceiver.decodedIRData.command;
    switch (latestCommand){
      case 94: m3.move(50); m3.run(); break;//button #3
      case 90: m3.move(-50); m3.run(); break;//button #6
      case 24: m2.move(50); m2.run(); break;//button #2
      case 28: m2.move(-50); m2.run(); break;//button #5
      case 12: m1p1.move(-50); m1p2.move(50); m1p1.run(); m1p2.run(); break; //button #1
      case 8:  m1p1.move(50); m1p2.move(-50); m1p1.run(); m1p2.run(); break; //button #4
      case 7:  base.move(50); base.run(); break; //button skip backward
      case 9:  base.move(-50); base.run(); break; //button skip foward
      case 64: // button + sign
        //close claw
        for (pos = 0; pos <= 92; pos += 1) { //we dont need to do this, we can tell it go to end position but it moves really fast
          clawServo.write(pos);              
          delay(15);                       
        }
        break;
      case 25: //button -sign
        //open claw
        for (pos = 92; pos >= 0; pos -= 1) { 
          clawServo.write(pos);              
          delay(15);                       
        }
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
