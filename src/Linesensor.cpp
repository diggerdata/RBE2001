#include "Arduino.h"
#include "Linesensor.h"
#include "RobotMap.h"

Linesensor::Linesensor() {
}


unsigned char Linesensor::getArray() {
    unsigned char linesensorChar = 0;

    for (unsigned char i = 0; i < 8; ++i)
    {
        if (getSensor(linesensorArray[i])) {
            linesensorChar <<= 1;
            linesensorChar |= 0b1;
        }
    }

    return linesensorChar;
}

bool getSensor(int number) {
  return analogRead(number);
}
