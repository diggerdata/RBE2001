/*
 *  Arm.cpp
 *
 *  Created on: 2/26/17
 *      Author: james
 */

#include "Arduino.h"
#include "Arm.h"
#include "RobotMap.h"
#include <Servo.h>


Arm::Arm() {}

void Arm::attach (unsigned char armMotorPort, unsigned char potPort, unsigned char gripServoPort) {
    pot = potPort;
    armMotor.attach(armMotorPort, 1000, 2000);
    gripServo.attach(gripServoPort, 1000, 2000);
}

void Arm::setHigh () {      //bypasses update();
    set (HIGHPOS);    // stops
}

void Arm::setLow () {      //bypasses update();
    set (LOWPOS);    // stops
}

void Arm::stop () { //stop
    armSpeed = MTRSTOP;
}

void Arm::instantStop () {      //bypasses update();
    armMotor.write(MTRSTOP);    // stops
}

void Arm::updatePot () {
    armCurrentPoint = analogRead(pot);
}

void Arm::set (int pos) {      //bypasses update();
    armSetPoint = pos;    // stops
}

int Arm::pid() {
    return pid(armSetPoint, armCurrentPoint);
}

int Arm::pid (int setpoint, int currentpoint) {
  int error = setpoint - currentpoint;
  // int inttime = millis() - lastTime;
  // int lasterror = error;
  return (kp * error); // + (ki * (integral += (error * inttime))) + (kd * (error-lasterror));
}

void Arm::update() {
    updatePot();
    armMotor.write(MTRSTOP + pid());
}
