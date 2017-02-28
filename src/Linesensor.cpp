#include "Arduino.h"
#include "Linesensor.h"
#include "RobotMap.h"

Linesensor::Linesensor() {
}


unsigned char Linesensor::getArray() {
    return sensorState;
}

bool Linesensor::getSensor(int number) {
    // Serial.print(digitalRead(number));
    // Serial.println(analogRead(number));
    return digitalRead(number);
}

void Linesensor::update() {
    volatile unsigned char linesensorChar = 0;
    // volatile unsigned long temp = 0;

    for (unsigned char i = 0; i < 8; ++i) {
        linesensorChar <<= 1;
        // temp *= 10;
        if (getSensor(linesensorArray[i])) {
            linesensorChar |= 0b1;
            // temp += 1;

        }
    }

    sensorState = linesensorChar;

    // Serial.println("sensor = " + temp);
    Serial.print("sensor = ");
    Serial.println(sensorState);
}
