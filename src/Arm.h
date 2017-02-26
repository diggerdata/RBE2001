/*
 *  Arm.h
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
class Arm {
    public:
        Arm(unsigned char armMotorPort, unsigned char potPort, unsigned char gripServoPort);
        void update();
        void stop();
        void instantStop();

    private:

        int pid (int setpoint, int currentpoint);
        int pid ();

        signed char armSpeed;       //arm speed variable
        signed char gripPos;        //grip pos variable

        unsigned char armSetPoint;     //arm pid
        unsigned char armCurrentPoint; //arm pid

        long integral = 0;
        long lastTime = 0;
        float lasterror = 0;

        Servo armMotor;       // create servo object to control arm motor
        Servo gripServo;       // create servo object to control grip servo

};

#endif /* DRIVE_H_ */
