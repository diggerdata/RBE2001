#include "RobotMap.h"
#include <Arduino.h>
#include <Servo.h>
#include "Messages.h"

long lastTime = 0;
long integral = 0;
float lasterror = 0;

Messages msg;
unsigned long timeForHeartbeat;

Servo drivel;       // create servo object to control left drive motor
Servo driver;       // create servo object to control right drive motor
Servo arml;         // create servo object to control left arm motor
Servo armr;         // create servo object to control right arm motor
Servo armg;         // create servo object to control finger servo

void setup() {

  Serial.begin(9600); // Serial output begin

  Serial.println("Starting");
  msg.setup();
  timeForHeartbeat = millis() + 1000;

  drivel.attach(mtrL, 1000, 2000);
  driver.attach(mtrR, 1000, 2000);
  arml.attach(mtrAL, 1000, 2000); //is correct?
  armr.attach(mtrAR, 1000, 2000);
  armg.attach(srvClmp, 1000, 2000);
}

void auton () { // auton by task number. Everything passed the commented out block is untested

}

void drive(int leftm, int rightm) { // barebones drive
  drivel.write(180 - leftm);    // Inverted for left side, so fwdmax is fwd
  driver.write(rightm);         // sets value to rightm
}

void armMove(int motorSpeed) {  // barebones arm drive
  arml.write(motorSpeed);       // sets arm to motor speed
  armr.write(180 - motorSpeed); // Inverted for side
}

void stopRobot () { //stop
  drivel.write(mtrStop);
  driver.write(mtrStop);
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
