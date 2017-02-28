#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

#include "Arduino.h"

static const float kp = 0, ki = 0, kd = 0;

static const unsigned char type = 0x00;
static const unsigned char src  = 0x01;
static const unsigned char dest = 0x02;

static const unsigned char mtrLF =  6;
static const unsigned char mtrLR =  7;
static const unsigned char mtrRF =  8;
static const unsigned char mtrRR =  9;

static const unsigned char mtrArm = 5;
static const unsigned char srvClmp = 4;
static const unsigned char potArm = A0;

static const unsigned char frontSwitch = 22;

static const unsigned char mtrFwd = 180; // run motor full-speed 'forward'
static const unsigned char mtrRwd = 0; // run motor full-speed 'reverse'
static const unsigned char mtrStop = 90; // stop motor
#define MTRSTOP 90

static const unsigned char ledpindebug = 13;

static const unsigned char linesensorArray [8] = {A1, A2, A3, A4, A5, A6, A7, A8};


#endif /* ROBOTMAP_H_ */
