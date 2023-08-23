// Include the AccelStepper Library (https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html)
#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>

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


void setup() {
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

  Serial.println(radiansToDegrees(angleAlpha(11,12.4,angleBeta(11,12.4))));
  Serial.println(radiansToDegrees(angleBeta(11,12.4)));
  
  
}

void loop() {
  
}

int angleToSteps(int angle) {
  //2048 is number of steps for one full rotation
  //with 1 to 3 gear ratio multiply number of steps by 3 ; 2048 * 3 = 6144
  //17 steps/degree
  return 17 * angle;
}

float angleAlpha (int x, int y, float beta){
  //arctan(y/x) - arctan((d1*sin(beta))/(d1+d2*cos(beta)));
  //first term
  double term1 = atan(y/x);
  //numerator of second term
  double numerator = d1*sin(beta);
  //denominator of second term
  double denominator = d1 + d2 * cos(beta);
  //second term
  double term2 = atan(numerator/denominator);
  double preciseAlpha = term1 - term2;
  Serial.println(beta);
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

int radiansToDegrees(float angle){
  double degrees = angle * 57.2958; //multiply by 57.2958 to convert from radians to degrees (57.2958 = 180/pi)
  return (int)degrees; //cast to int as motor steps are in ints
}

void runMotors() {
  base.run();
  m1p1.run();
  m1p2.run();
  m2.run();
  m3.run();
}