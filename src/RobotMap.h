#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

class RobotMap {
  public:

    const float kp = 0, ki = 0, kd = 0;

    const unsigned char type = 0x00;
    const unsigned char src  = 0x01;
    const unsigned char dest = 0x02;

    const unsigned char mtrL = 7;
    const unsigned char mtrR = 8;

    const unsigned char mtrAL = 6;
    const unsigned char mtrAR = 5;
    const unsigned char srvClmp = 4;

    const unsigned char armLimit = 22;
    const unsigned char rwdLimit = 23;

    const unsigned char armpot = 0xA0;
    const unsigned char linesensor = 0xA1;

    const unsigned char sideSwitch = 28;

    const unsigned char mtrFwd = 180; // run motor full-speed 'forward'
    const unsigned char mtrRwd = 0; // run motor full-speed 'reverse'
    const unsigned char mtrStop = 90; // stop motor

    const unsigned char ledpindebug = 13;

  };

#endif /* ROBOTMAP_H_ */
