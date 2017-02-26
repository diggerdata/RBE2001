#include "RobotMap.h"
#include <Arduino.h>

#include "Messages.h"
#include "Linesensor.h"

long lastTime = 0;
long integral = 0;
float lasterror = 0;

Messages msg;
unsigned long timeForHeartbeat;


Servo arml;         // create servo object to control left arm motor
Servo armr;         // create servo object to control right arm motor
Servo armg;         // create servo object to control finger servo
Linesensor linesensor;

void setup() {

  Serial.begin(9600); // Serial output begin

  Serial.println("Starting");
  msg.setup();
  timeForHeartbeat = millis() + 1000;


  arml.attach(mtrAL, 1000, 2000);
  armg.attach(srvClmp, 1000, 2000);
}

void auton () { // auton by task number. Everything passed the commented out block is untested

}

void armMove(int motorSpeed) {  // barebones arm drive
  arml.write(motorSpeed);       // sets arm to motor speed
}


signed char turn () { //code to turn
  char sensorValue = linesensor.getArray();

  if ((sensorValue | 0b00000000) == 0b11111111) {

  }

  if ((sensorValue | 0b00011000) == 0b11111111) {

  }

  return 0;
}

//////////////////////////////////////////////
// Stuff that shouldn't be touched too hard //
// Just saying.                             //
//////////////////////////////////////////////

void loop() {
  auton();  //calls the auton method
  if (msg.read()) {
    msg.printMessage();
  }
  if (millis() > timeForHeartbeat) {
    timeForHeartbeat = millis() + 1000;
    msg.sendHeartbeat();
    Serial.println("heartbeat");
  }
}

int PID (int setpoint, int currentpoint) {
  int error = setpoint - currentpoint;
  int inttime = millis() - lastTime;
  int lasterror = error;
  return (kp * error) + (ki * (integral += (error * inttime))) + (kd * (error-lasterror));
}
