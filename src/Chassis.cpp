/*
 *  Chassis.cpp
 *
 *  Created on: 2/26/17
 *      Author: james
 */

#include "Arduino.h"
#include "Chassis.h"
#include "RobotMap.h"
#include <Servo.h>

#define MTRSTOP 90

Chassis::Chassis(unsigned char leftMotor, unsigned char rightMotor) {
    drivel.attach(leftMotor, 1000, 2000);
    driver.attach(rightMotor, 1000, 2000);
}

void Chassis::stop () { //stop
    speedState = MTRSTOP;
    turnState = MTRSTOP;
}

void Chassis::instantStop () { //bypasses update();
    drivel.write(MTRSTOP);     // stops
    driver.write(MTRSTOP);     // stops
}

void Chassis::drive(signed char speed, signed char turn) { //go
    speedState = speed;
    turnState = turn;
}

void Chassis::update() {
    drivel.write(180 - (speedState + turnState));    // Inverted for left side, so fwdmax is fwd
    driver.write(speedState - turnState);         // sets value to rightm, turnState is clockwise positive
}
