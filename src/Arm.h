/*
 *  Arm.h
 *
 *  Created on: 2/26/17
 *      Author: james
 */

#ifndef ARM_H_
#define ARM_H_

#include <Arduino.h>
#include <Servo.h>

#define LOWPOS 0
#define HIGHPOS 0

/**
 * Handles linesensor information
 */
class Arm {
    public:
        Arm();
        void attach (unsigned char armMotorPort, unsigned char potPort, unsigned char gripServoPort);
        void setHigh ();
        void setLow ();
        void update();
        void stop();
        void instantStop();
        void openGrip();
        void closeGrip();

    private:

        unsigned char pot;

        void updatePot ();

        void set (int pos);

        int pid (int setpoint, int currentpoint);
        int pid ();

        signed char armSpeed = 0;       //arm speed variable
        signed char gripPos = 0;        //grip pos variable

        unsigned char armSetPoint = 0;     //arm pid
        unsigned char armCurrentPoint = 0; //arm pid

        long integral = 0;
        long lastTime = 0;
        float lasterror = 0;

        Servo armMotor;       // create servo object to control arm motor
        Servo gripServo;       // create servo object to control grip servo

};

#endif /* ARM_H_ */
