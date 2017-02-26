#include "Arduino.h"
#include "Linesensor.h"
#include "RobotMap.h"

Linesensor::Linesensor() {
}


unsigned char Linesensor::getArray() {
    return sensorState;
}

bool getSensor(int number) {
  return analogRead(number);
}

void Linesensor::update() {
    volatile unsigned char linesensorChar = 0;

    for (unsigned char i = 0; i < 8; ++i)
    {
        if (getSensor(linesensorArray[i])) {
            linesensorChar <<= 1;
            linesensorChar |= 0b1;
        }
    }

    sensorState = linesensorChar;
}
