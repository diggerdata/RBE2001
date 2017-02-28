#include "RobotMap.h"
#include <Arduino.h>

#include "Messages.h"
#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"



Messages msg;
unsigned long timeForHeartbeat;
unsigned long timeForCommit;


Linesensor linesensor;
Chassis chassis;
Arm arm;

void setup() {

  Serial.begin(9600); // Serial output begin

  Serial.println("Starting");
  msg.setup();
  timeForHeartbeat = millis() + 1000;
  timeForCommit = millis() + 100;

  chassis.attach(mtrLF, mtrRF, mtrLR, mtrRR);
  arm.attach(mtrArm, potArm, srvClmp);

  chassis.instantStop();
  arm.instantStop();

}

void auton () { // auton by task number. Everything passed the commented out block is untested

}

void update () { // update method. Call this to excecute stored states
    if (msg.isStopped()) {
        chassis.instantStop();
        arm.instantStop();
    } else {
        chassis.update();
        arm.update();
    }

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
  if (millis() > timeForCommit) {
    timeForCommit = millis() + 100;
    update();
    Serial.println("commit");
  }
}
