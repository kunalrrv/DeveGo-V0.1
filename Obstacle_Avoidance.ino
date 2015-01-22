//#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <NewPing.h>

#define TRIGGER_PIN  14  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     15  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 //speed variables for the left and right motor
int Lspeed = 180;
int Rspeed = 180;

//declaring the left and right motors and attaching them to 
//their corresponding connector on the motor shield
//AF_DCMotor leftMotor(1, MOTOR12_64KHZ);
//AF_DCMotor rightMotor(2, MOTOR12_64KHZ);

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(3);

void setup() {
  Serial.begin(9600);
  //sets initial speed
  AFMS.begin();
  myMotor -> setSpeed(Lspeed);
  myOtherMotor -> setSpeed(Rspeed);
}

void loop() {
  //unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
      unsigned int CM = DistanceSensor.ping_cm();
  Serial.print("Distance: ");
    Serial.print(CM);
    Serial.println("cm");
    delay(1000);

  if (CM < 5 && CM > 0) {
    int iteration = 0;
    while( iteration == 0){
      myMotor ->run(BACKWARD);
      myOtherMotor -> run(BACKWARD);
      delay(600);
      myMotor ->run(FORWARD);
      myOtherMotor -> run(BACKWARD);
      iteration = 1;
    }
    delay(600);
  }
  
  //starts motors going forward
  myMotor ->run(FORWARD);
      myOtherMotor -> run(FORWARD);
  }
