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
volatile int gripTime = 0;

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
      case kDriveToReactorInitial:
          if(true /*limit switch is not pressed*/) {
            chassis.drive(mtrFwd);
          }
          else {
            chassis.stop();
            state = kArmDownInitial;
          }
          break;

      case kArmDownInitial:
          if(arm.getPot() <= 620) {
            state = kCloseGripInitial;
          }
          else {
            arm.setLow();
          }
          break;

      case kCloseGripInitial:
          static unsigned int lastTime = millis();
          arm.closeGrip();
          if (millis() > lastTime + 1000) {
              state = kArmUpInitial;
          }
          break;

      case kArmUpInitial:
          if(arm.getPot() >= 880) {
            state = kBackUpInitial;
          }
          else {
            arm.setHigh();
          }
          break;

      case kBackUpInitial:
        static unsigned int timeToStop1 = millis();
        if (millis() > timeToStop1 + 1000) {
            state = kTurnAroundInitial;
          }
        else {
          chassis.drive(mtrRwd);
        }
        break;

      case kTurnAroundInitial:
          if(linesensor.getArray() || !(BIT3 && BIT4) == !(BIT3 && BIT4)) {
              chassis.stop();
              state = kDriveToLineInitial;
          }
          else {
            chassis.turn(50);
          }
          break;

      case kDriveToLineInitial:
          if(linesensor.getArray() == 0) {
              state = kStopAfterLineInitial;
                }
          else {
            chassis.drive(mtrFwd);
          }
          break;

      case kStopAfterLineInitial:
            static unsigned int timeToStop2 = millis();
            if (millis() > timeToStop2 + 1000) {
                state = kTurnToStorageInitial;
              }
              else{
                chassis.drive(mtrFwd);
              }
          break;

      case kTurnToStorageInitial:
          if(linesensor.getArray() || !(BIT3 && BIT4) == !(BIT3 && BIT4)) {
            chassis.stop();
            state = kDriveToStorage;
          }
          else {
            chassis.turn(50);
          }
          break;

      case kDriveToStorage:
          if(true /*limit switch is not pressed*/) {
            chassis.drive(mtrFwd);
          }
          else {
            chassis.stop();
            state = kReleaseSpent;
          }
          break;

      case kReleaseSpent:
          static unsigned int timeToStop3 = millis();
          if (millis() > timeToStop3 + 1000) {
              state = kBackUpStorage;
            }
          else {
              
          }
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
