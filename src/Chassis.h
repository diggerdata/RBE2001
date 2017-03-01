/*
 *  Chassis.h
 *
 *  Created on: 2/26/17
 *      Author: james
 */

#ifndef DRIVE_H_
#define DRIVE_H_

#include <Arduino.h>
#include <Servo.h>

/**
 * Handles linesensor information
 */
class Chassis {
    public:
        Chassis();
        void attach(unsigned char leftMotorFwd, unsigned char leftMotorRwd, unsigned char rightMotorFwd, unsigned char rightMotorRwd);
        void attachEnc(unsigned char leftEncA, unsigned char leftEncB, unsigned char rightEncA, unsigned char rightEncB);
        void drive(signed char speed, signed char turn);
        void update();
        void stop();
        void instantStop();
        void drive(signed char speed);
        void turn(signed char turn);

    private:

        void LeftLeftEncoderISR();
        void RightEncoderISR();

        signed char speedState = 0;
        signed char turnState = 0;

        unsigned char driveLF;       // create char to map left drive motor
        unsigned char driveRF;       // create char to map right drive motor
        unsigned char driveLR;       // create char to map left drive motor
        unsigned char driveRR;       // create char to map right drive motor

        unsigned char encLA;       // create char to map left encoder
        unsigned char encLB;       // create char to map right encoder
        unsigned char encRA;       // create char to map left encoder
        unsigned char encRB;       // create char to map right encoder



};

#endif /* DRIVE_H_ */
