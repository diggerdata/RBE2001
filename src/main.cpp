#include "RobotMap.h"
#include <Arduino.h>

#include "Messages.h"
#include "Linesensor.h"



Messages msg;
unsigned long timeForHeartbeat;


Linesensor linesensor;

void setup() {

  Serial.begin(9600); // Serial output begin

  Serial.println("Starting");
  msg.setup();
  timeForHeartbeat = millis() + 1000;


}

void auton () { // auton by task number. Everything passed the commented out block is untested

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
