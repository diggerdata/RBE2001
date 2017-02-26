/*
 * Linesensor.h
 *
 *  Created on: 2/24/17
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
        Chassis(unsigned char leftMotor, unsigned char rightMotor);
        void drive(signed char speed, signed char turn);
        void update();
        void stop();
        void instantStop();

    private:
        signed char speedState;
        signed char turnState;
        Servo drivel;       // create servo object to control left drive motor
        Servo driver;       // create servo object to control right drive motor

};

#endif /* DRIVE_H_ */
