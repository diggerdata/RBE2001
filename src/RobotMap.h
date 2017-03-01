#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

#include <Arduino.h>



static const unsigned char type = 0x00;
static const unsigned char src  = 0x01;
static const unsigned char dest = 0x02;

static const unsigned char mtrLF =  6;
static const unsigned char mtrLR =  7;
static const unsigned char mtrRF =  8;
static const unsigned char mtrRR =  9;

static const unsigned char mtrArm = 5;
static const unsigned char srvClmp = 4;
static const unsigned char potArm = A1;

static const unsigned char frontSwitch = 22;

static const signed char mtrFwd = -50; // run motor full-speed 'forward'
static const signed char mtrRwd = 50; // run motor full-speed 'reverse'
static const signed char mtrStop = 0; // stop motor
#define MTRSTOP 90

static const unsigned char ledpindebug = 13;

static const unsigned char linesensorArray [8] = {A0, A2, A3, A4, A5, A6, A7, A8};

enum States {
  kDriveToReactorInitial, //Robot starts the process of extracting spent rod
  kArmDownInitial,
  kCloseGripInitial,
  kArmUpInitial,
  kBackUpInitial,
  kDriveToLine,
  kTurnAroundInitial,
  kDriveToLineInitial,
  kStopAfterLineInitial,  //from here, begin storing the spent rod
  kTurnToStorageInitial,
  kDriveToStorage,
  kReleaseSpent,
  kBackUpStorage,
  kTurnFromStorage,
  kDriveFromStorage,
  kStopAfterLineStorage,
  kTurnToReactorStr,
  kDriveToReactorStr, //drives off of horizontal lines, then begin getting supply
  kTurnAroundToSupply,
  kDriveToLineSply,
  kStopPastLineSply,
  kTurnToStorageSecondary,
  kDriveToSupply,
  kGrabSupply,
  kBackUpSupply,
  kTurnFromSupply,
  kDriveFromSupply,
  kTurnToReactorSply,
  kDriveToReactorSply,
  kLowerNewRod,
  kReleaseNewRod,
  kArmUpFinal
};

enum Bits {
  BIT0 = 0b00000001,
  BIT1 = 0b00000010,
  BIT2 = 0b00000100,
  BIT3 = 0b00001000,
  BIT4 = 0b00010000,
  BIT5 = 0b00100000,
  BIT6 = 0b01000000,
  BIT7 = 0b10000000 //standard bitwise operators
};

#endif /* ROBOTMAP_H_ */
