#include <Servo.h>

Servo clawServo; 

int pos = 0;    // variable to store the servo position

void setup() {
  clawServo.write(0);
  clawServo.attach(13); 
  delay(5000); 
}

void loop() {
  for (pos = 0; pos <= 92; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    clawServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = 92; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    clawServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}