#include "RobotMap.h"
#include <Arduino.h>

#include "Messages.h"
#include "Chassis.h"
#include "Arm.h"
#include "Linesensor.h"

// #include "EncoderRight.c"

Messages msg;
unsigned long timeForHeartbeat;
unsigned long timeForPush;

volatile unsigned int tubeLinesCrossed = 0;

Linesensor linesensor;
Chassis chassis;
Arm arm;
States state;
void setup() {

  Serial.begin(9600); // Serial output begin


  // pinMode(c_LeftEncoderPinA, INPUT_PULLUP);      // sets pin A as input
  // pinMode(c_LeftEncoderPinB, INPUT_PULLUP);      // sets pin B as input
  // attachInterrupt(c_LeftEncoderInterruptA, HandleLeftMotorInterruptA, CHANGE);
  // attachInterrupt(c_LeftEncoderInterruptB, HandleLeftMotorInterruptB, CHANGE);
  //
  // pinMode(c_RightEncoderPinA, INPUT_PULLUP);      // sets pin A as input
  // pinMode(c_RightEncoderPinB, INPUT_PULLUP);      // sets pin B as input
  // attachInterrupt(c_RightEncoderInterruptA, HandleRightMotorInterruptA, CHANGE);
  // attachInterrupt(c_RightEncoderInterruptB, HandleRightMotorInterruptB, CHANGE);


  Serial.println("Starting");
  msg.setup();
  timeForHeartbeat = millis() + 1000;
  timeForPush = millis() + 100;

  chassis.attach(mtrLF, mtrLR, mtrRF, mtrRR);
  arm.attach(mtrArm, potArm, srvClmp);

  chassis.instantStop();
  arm.instantStop();
  linesensor.init();

  arm.openGrip();
}

void auton () { // auton by task number. Everything passed the commented out block is untested
    chassis.drive(0, 0);
    switch (state) {
      case kDriveToReactor:
          if(true /*limit switch is not pressed*/) {
            chassis.drive(mtrFwd);
          }
          else {
            chassis.stop();
            state = kArmDown;
          }
          break;

      case kArmDown:
          if(true /*robot is on a line*/) {

          }
          break;

      case kArmUp:
          if((msg.getStorageAvl() && BIT0) == BIT0) { //SHOULD check if closest tube is open. Might be backwards
            //drive until first line, then turn.
            //get rod, then turn around and drive until line.
            //drive back to reactor and turn around, like above
          }

          else {
            chassis.stop();
            Serial.println("ERROR: Bluetooth message incorrect");
            //LED flashing for visual indication
          }
          break;

      case kTurnAround:
          if((msg.getSupplyAvl() && BIT0) == BIT0) { //SHOULD check if closest tube is open. Might be backwards
            //drive until first line, then turn.
            //get rod, then turn around and drive until line
            //drive back to reactor
          }
          else if((msg.getSupplyAvl() && BIT1) == BIT1) {  //checks if next tube is open
            //drive until second line
            //get rod, then turn around and drive until line
            //drive back to reactor
          }
          else if(((msg.getSupplyAvl() && BIT2) == BIT2)) {  //etc
            //drive until third line
            //get rod, then turn around and drive until line
            //drive back to reactor
          }
          else if((msg.getSupplyAvl() && BIT3) == BIT3) {  //checks if last tube is open
            //drive until fourth line
            //get rod, then turn around and drive until line
            //drive back to reactor
          }
          else {
            chassis.stop();
            Serial.println("ERROR: Bluetooth message incorrect");
            //LED flashing for visual indication
          }
          break;

      case kDriveToLine:
          while(true /*limit switch is not pressed*/)
            chassis.drive(mtrFwd);
          arm.setLow();
          arm.openGrip();
          //some delay
          arm.setHigh();
          break;
          default:
          Serial.print("ERROR");
          //make LED flash for visual indication

          break;
    }
}

void update () { // update method. Call this to excecute stored states


    // getEncTicksLeft();
    // getEncTicksRight();

    if (msg.isStopped()) {
        chassis.instantStop();
        arm.instantStop();
    } else {
        chassis.update();
        arm.update();
    }
    linesensor.update();

}

signed char turn () { //code to turn. 0= line detected 1= no line
  char sensorValue = linesensor.getArray();

  if ((sensorValue | 0b00000000) == 0b11111111) {
      chassis.drive(0, 0);
  }

  if ((sensorValue | 0b00011000) == 0b11111111) {
      chassis.turn(0);
  }

  if ((sensorValue | 0b11100000) == 0b11111111) {
      chassis.turn(20);
  }

  if ((sensorValue | 0b00000111) == 0b11111111) {
      chassis.turn(-20);
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
  if (millis() > timeForPush) {
    timeForPush = millis() + 100;
    update();
    // Serial.println("pushed");
  }
}
