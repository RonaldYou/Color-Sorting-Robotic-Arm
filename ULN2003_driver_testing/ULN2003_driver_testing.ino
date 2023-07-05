//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2048;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper1 = Stepper(stepsPerRevolution, 0, 2, 1, 3);
Stepper myStepper2 = Stepper(stepsPerRevolution, 4, 6, 5, 7);
Stepper myStepper3 = Stepper(stepsPerRevolution, 8, 10, 9, 11);
//Stepper myStepper4 = Stepper(stepsPerRevolution, 12, A0, 13, A1);
Stepper myStepper5 = Stepper(stepsPerRevolution, A2, A4, A3, A5);

  


int xValue = analogRead(A0);
int yValue = analogRead(A1);


 int xValueBase = 497;
int yValueBase = 507;


void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
    //Serial.begin(9600);
  //   Serial.print("xBASEEEEEEEEEEeee = ");
  // Serial.print(xValue);
  // Serial.print("  yBASEEEEEEEEEEEEe = ");
  // Serial.print(yValue);
  // Serial.println();


 
}

void loop() {
  
  myStepper1.setSpeed(10);
  myStepper2.setSpeed(10);
  myStepper3.setSpeed(10);
  // myStepper1.step(100);
  // myStepper1.step(-100);
  // for(int i=0;i<stepsPerRevolution;i++){
  //   if(i<=int(stepsPerRevolution/5)){
  //     myStepper1.step(1);
  //   }   
  //   if(i<=int(stepsPerRevolution/5)){
  //     myStepper3.step(1);
  //   }
  //   if(i<=int(stepsPerRevolution/5)){
  //     myStepper2.step(1);
  //   }
  // }
  // //delay(1000);
  // for(int i=0;i>-(stepsPerRevolution);i--){
  //   if(i>=-int(stepsPerRevolution/5)){
  //     myStepper1.step(-1);
  //   }   
  //   if(i>=-int(stepsPerRevolution/5)){
  //     myStepper3.step(-1);
  //   }
  //   if(i>=-int(stepsPerRevolution/5)){
  //     myStepper2.step(-1);
  //   }
  //  }
  delay(1000);

	// myStepper4.setSpeed(10);
  // myStepper4.step(stepsPerRevolution/3);
  // myStepper4.step(-stepsPerRevolution/3);

  // myStepper5.setSpeed(10);
  // myStepper5.step(stepsPerRevolution/3);
  // myStepper5.step(-stepsPerRevolution/3);

  // int xValue = analogRead(A0);
  // int yValue = analogRead(A1);
  // Serial.print("x = ");
  // Serial.print(xValue);
  // Serial.print("  y = ");
  // Serial.print(yValue);
  // Serial.println();
  // if(xValue > xValueBase + 100){
  //   myStepper1.step(50);
  // }
  // else if(xValue < xValueBase - 100){
  //   myStepper1.step(-50);
  // }

  // if(yValue > yValueBase + 100){
  //   myStepper2.step(50);
  // }
  // else if(yValue < yValueBase - 100){
  //   myStepper2.step(-50);
  // }

}
