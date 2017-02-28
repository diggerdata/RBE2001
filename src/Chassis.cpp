/*
 *  Chassis.cpp
 *
 *  Created on: 2/26/17
 *      Author: james
 */

#include "Arduino.h"
#include "Chassis.h"
#include <Servo.h>

Chassis::Chassis(){}

void Chassis::attach(unsigned char leftMotorFwd, unsigned char rightMotorFwd, unsigned char leftMotorRwd, unsigned char rightMotorRwd) {
    driveLF =  leftMotorFwd;
    driveRF = rightMotorFwd;
    driveLR =  leftMotorRwd;
    driveRR = rightMotorRwd;

    speedState = 0;
    turnState = 0;

    pinMode(driveLF, OUTPUT);
    pinMode(driveRF, OUTPUT);
    pinMode(driveLR, OUTPUT);
    pinMode(driveRR, OUTPUT);

}

void Chassis::stop () { //stop
    speedState = 0;
    turnState = 0;
}

void Chassis::instantStop () { //bypasses update();
    pinMode(driveLF, 0);
    pinMode(driveRF, 0);
    pinMode(driveLR, 0);
    pinMode(driveRR, 0);
}

void Chassis::drive(signed char speed, signed char turn) { //go
    speedState = speed;
    turnState = turn;
}

void Chassis::update() {

    signed char currLeftSpeed;
    signed char currRightSpeed;

    if ((int)speedState + (int)turnState > 127) {
        currLeftSpeed =  127;
    } else if ((int)speedState + (int)turnState < -127) {
        currLeftSpeed = -127;
    } else {
        currLeftSpeed = speedState + turnState;
    }

    if ((int)speedState - (int)turnState > 127) {
        currRightSpeed =  127;
    } else if ((int)speedState - (int)turnState < -127) {
        currRightSpeed = -127;
    } else {
        currRightSpeed = speedState - turnState;
    }

    Serial.println("MOTOR LEFT : " + 0 + '\0');
    Serial.println("MOTOR RIGHT: " + 0 + '\0');

    if (currLeftSpeed > 0) {
        pinMode(driveLF,  2 * currLeftSpeed);
        pinMode(driveLR, 0);

    } else {
        pinMode(driveLF, 0);
        pinMode(driveLR, -2 * currLeftSpeed);

    }

    if (currRightSpeed > 0) {
        pinMode(driveRF, -2 * currRightSpeed);
        pinMode(driveRR, 0);

    } else {
        pinMode(driveRF, 0);
        pinMode(driveRR,  2 * currRightSpeed);

    }


}
