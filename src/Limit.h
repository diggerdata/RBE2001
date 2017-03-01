/*
 *  Arm.h
 *
 *  Created on: 2/26/17
 *      Author: james
 */

#ifndef LIMIT_H_
#define LIMIT_H_

#include <Arduino.h>
#include <Servo.h>

#define LOWPOS 0
#define HIGHPOS 0

/**
 * Handles linesensor information
 */
class Limit {
    public:
        Limit();
        void attach (unsigned char port);
        bool get();

    private:

};

#endif /* ARM_H_ */
