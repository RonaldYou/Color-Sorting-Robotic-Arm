// Include the AccelStepper Library (https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html)
#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>
#include <IRremote.h>

//Base
const int dirPinB = 2;
const int stepPinB = 3;

//Motor 1p1
const int dirPin1 = 4;
const int stepPin1 = 5;

//Motor 1p2
const int dirPin2 = 6;
const int stepPin2 = 7;

//Motor 2
const int dirPin3 = 8;
const int stepPin3 = 9;

//Motor 3
const int dirPin4 = 10;
const int stepPin4 = 11;


// Define motor interface type
#define motorInterfaceType 1  //type 1 is driver control
#define IR_RECEIVE_PIN A5

// Createing instances of motors
AccelStepper base(motorInterfaceType, stepPinB, dirPinB);
AccelStepper m1p1(motorInterfaceType, stepPin1, dirPin1);
AccelStepper m1p2(motorInterfaceType, stepPin2, dirPin2);
AccelStepper m2(motorInterfaceType, stepPin3, dirPin3);
AccelStepper m3(motorInterfaceType, stepPin4, dirPin4);


Servo clawServo;
int pos = 0;
int phase = 0;
const int d1 = 10; //cm
const int d2 = 10; //cm
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
  m1p1.setAcceleration(30);
  m1p1.setSpeed(75);

  m1p2.setMaxSpeed(1000);
  m1p2.setAcceleration(30);
  m1p2.setSpeed(75);

  m2.setMaxSpeed(1000);
  m2.setAcceleration(20);
  m2.setSpeed(50);

  m3.setMaxSpeed(1000);
  m3.setAcceleration(25);
  m3.setSpeed(90);

  clawServo.write(0);
  clawServo.attach(13);

  base.setCurrentPosition(0);
  m1p1.setCurrentPosition(0);
  m1p2.setCurrentPosition(0);
  m2.setCurrentPosition(0);
  m3.setCurrentPosition(0);

  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);

  //m1Move(angleToSteps(90));
}

void loop() {
  if(phase == 0){
    rotateTo(12,-10);
    if(m1p1.distanceToGo() == 0 && m1p2.distanceToGo() == 0 && m2.distanceToGo() == 0 && m3.distanceToGo() == 0){
      phase = 1;
      for (pos = 0; pos <= 92; pos += 1) { 
        clawServo.write(pos);              
        delay(15);                       
      }
      delay(500);
    }
    runMotors();
  }
  else if(phase == 1){
    rotateTo(15,0);
    clawServo.write(pos); 
    if(base.distanceToGo() == 0 && m1p1.distanceToGo() == 0 && m1p2.distanceToGo() == 0 && m2.distanceToGo() == 0){
      phase = 2;
    }
    runMotors();
  }
  else if(phase == 2){
    base.moveTo(1500);
    clawServo.write(pos); 
    if(base.distanceToGo() == 0 && m1p1.distanceToGo() == 0 && m1p2.distanceToGo() == 0 && m2.distanceToGo() == 0){
      phase = 3;
    }
    runMotors();
  }
  else if(phase == 3){
    rotateTo(12,-10);
    clawServo.write(pos); 
    if(base.distanceToGo() == 0 && m1p1.distanceToGo() == 0 && m1p2.distanceToGo() == 0 && m2.distanceToGo() == 0){
      phase = 4;
      for (pos = 92; pos >=0; pos--) { 
        clawServo.write(pos);              
        delay(15);                       
      }
      delay(500);
    }
    runMotors();
  }
  else if(phase == 4){
    m1p1.moveTo(0);
    m1p2.moveTo(0);
    if(m1p1.distanceToGo() == 0){
      phase = 5;
    }
    runMotors();
  }
  else if(phase == 5){
    m2.moveTo(0);
    if(m2.distanceToGo() <= 600){
      m3.moveTo(0);
    }
    if(base.distanceToGo() == 0 && m1p1.distanceToGo() == 0 && m1p2.distanceToGo() == 0 && m2.distanceToGo() == 0){
      phase = 6;
    }
    runMotors();
  }
  else{
    remoteControl();
  }
  runMotors();
}

void rotateTo(int x, int y){
  int alpha = radiansToDegrees(angleAlpha(x,y,angleBeta(x,y)));
  int beta = radiansToDegrees(angleBeta(x,y));
  int theta = radiansToDegrees(angleTheta(angleAlpha(x,y,angleBeta(x,y)), angleBeta(x,y)));

  Serial.println(radiansToDegrees(angleAlpha(x,y,angleBeta(x,y))));
  Serial.println(radiansToDegrees(angleBeta(x,y)));
  Serial.println(radiansToDegrees(angleTheta(angleAlpha(x,y,angleBeta(x,y)), angleBeta(x,y))));
  
  m1Move(angleToSteps(alpha));
  m3.moveTo(angleToStepsM3(theta-6));
  m2.moveTo(angleToSteps(beta));
  
  runMotors();
}

int angleToSteps(int angle) {
  //2048 is number of steps for one full rotation
  //with 1 to 3 gear ratio multiply number of steps by 3 ; 2048 * 3 = 6144
  //17 steps/degree
  return 17 * angle;
}

int angleToStepsM3(int angle){
  //2048 is number of steps for one full rotation
  //with 1 to 2 gear ration multiply number of steps by 2; 2048 * 2 = 4096
  //about 11.4 steps/degree
  return (int)11.4*angle;
}

float angleAlpha (float x, float y, float beta){
  //arctan(x/y) - arctan((d1*sin(beta))/(d1+d2*cos(beta)));
  //first term
  double term1 = atan(x/y);
  //numerator of second term
  double numerator = d1*sin(beta);
  //denominator of second term
  double denominator = d1 + d2 * cos(beta);
  //second term
  double term2 = atan(numerator/denominator);
  double preciseAlpha = term1 - term2;
  if(preciseAlpha < 0){
    preciseAlpha  = 3.14156 + preciseAlpha;
  }
  return (float)preciseAlpha;
}

float angleBeta (float x, float y){
  //returns radians
  //arccos((x^2 + y^2 - d1^2 - d2^2)/2*d1*d2)
  //numerator
  double numerator = sq(x) + sq(y) - sq(d1) - sq(d2);
  //denominator
  double denominator = 2 * d1 * d2;
  double preciseBeta = acos(numerator/denominator); 
  return (float)preciseBeta; //in radians
}

float angleTheta(float alpha, float beta){
  //pi/2 - (pi/2 - alpha - beta)
  return alpha + beta; 
}

int radiansToDegrees(float angle){
  double degrees = angle * 57.2958; //multiply by 57.2958 to convert from radians to degrees (57.2958 = 180/pi)
  return (int)degrees; //cast to int as motor steps are in ints
}

int m1Move(int steps){
  m1p1.moveTo(-steps);
  m1p2.moveTo(steps);
}

void remoteControl(){
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
}

void runMotors() {
  base.run();
  m1p1.run();
  m1p2.run();
  m2.run();
  m3.run();
}