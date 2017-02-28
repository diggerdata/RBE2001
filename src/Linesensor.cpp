#include "Arduino.h"
#include "Linesensor.h"
#include "RobotMap.h"

Linesensor::Linesensor() {
}


unsigned char Linesensor::getArray() {
    return sensorState;
}

void Linesensor::init() {
    pinMode(linesensorArray[0], INPUT);
    pinMode(linesensorArray[1], INPUT);
    pinMode(linesensorArray[2], INPUT);
    pinMode(linesensorArray[3], INPUT);
    pinMode(linesensorArray[4], INPUT);
    pinMode(linesensorArray[5], INPUT);
    pinMode(linesensorArray[6], INPUT);
    pinMode(linesensorArray[7], INPUT);
}

bool Linesensor::getSensor(int number) {
    // Serial.print(digitalRead(number));
    Serial.print(analogRead(number));
    Serial.print('\t');
    return digitalRead(number);
}

void Linesensor::update() {
    volatile unsigned char linesensorChar = 0b0;
    volatile unsigned long temp = 8;

    for (unsigned char i = 0; i < 8; ++i) {
        linesensorChar <<= 1;
        temp *= 10;
        if (getSensor(linesensorArray[i])) {
            linesensorChar |= 0b1;


        } else {
            temp += 1;
        }



    }

    sensorState = 0b11111111 ^ linesensorChar;

    Serial.print("sensor = ");
    Serial.println(temp);
    // Serial.print("sensor = ");
    // Serial.println(sensorState);
}
