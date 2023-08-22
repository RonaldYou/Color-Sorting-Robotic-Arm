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
  m3.setMaxSpeed(1000);
	m3.setAcceleration(100);
	m3.setSpeed(100);

  m3.setCurrentPosition(0);

  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
}
void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);
    latestCommand = IrReceiver.decodedIRData.command;
    if(latestCommand == 94){ //button #3
      m3.move(50);
      
    }
    m3.run();
    if(latestCommand == 90){ //button #6
      m3.move(-50);
    }
    IrReceiver.resume();
  }
  m3.run();
}
