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

#define LOWPOS 680 //APPROXIMATE values, dependent on battery
#define HIGHPOS 880

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
        unsigned char getPot();

    private:

        unsigned short pot;

        void updatePot ();

        void set (int pos);

        int pid (int setpoint, int currentpoint);
        int pid ();

        signed char armSpeed = 0;       //arm speed variable
        unsigned char gripPos = 0;        //grip pos variable

        unsigned short armSetPoint = 0;     //arm pid
        unsigned short armCurrentPoint = 0; //arm pid

        long integral = 0;
        long lastTime = 0;
        float lasterror = 0;

        Servo armMotor;       // create servo object to control arm motor
        Servo gripServo;       // create servo object to control grip servo

};

#endif /* ARM_H_ */
