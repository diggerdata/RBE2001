/*
 * Linesensor.h
 *
 *  Created on: 2/24/17
 *      Author: james
 */

#ifndef LINESENSOR_H_
#define LINESENSOR_H_

/**
 * Handles linesensor information
 */
class Linesensor {
  public:
    Linesensor();
    unsigned char getArray(); //returns a char with a 1 in each bit for each sensor
    void update();

  private:
    unsigned char sensorState;
    bool getSensor(int number); //1 to 8

};

#endif /* LINESENSOR_H_ */
