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
        void attach(unsigned char leftMotorFwd, unsigned char rightMotorFwd, unsigned char leftMotorRwd, unsigned char rightMotorRwd);
        void drive(signed char speed, signed char turn);
        void update();
        void stop();
        void instantStop();
        void drive(signed char speed);
        void turn(signed char turn);

    private:
        signed char speedState = 0;
        signed char turnState = 0;
        unsigned char driveLF;       // create servo object to control left drive motor
        unsigned char driveRF;       // create servo object to control right drive motor
        unsigned char driveLR;       // create servo object to control left drive motor
        unsigned char driveRR;       // create servo object to control right drive motor



};

#endif /* DRIVE_H_ */
