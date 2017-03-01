#ifndef ENCR_H_
#define ENCR_H_
/*
*adapted from http://yameb.blogspot.com/2012/11/quadrature-encoders-in-arduino-done.html
*Quadrature Decoder
*/
#include "Arduino.h"

// It turns out that the regular digitalRead() calls are too slow and bring the arduino down when
// I use them in the interrupt routines while the motor runs at full speed.

// Quadrature encoders
// Right encoder

//Mega2560	2  3 21  20  19  18

#define c_RightEncoderInterruptA 0
#define c_RightEncoderInterruptB 1
#define c_RightEncoderPinA 2
#define c_RightEncoderPinB 3
#define RightEncoderIsReversed

volatile bool _RightEncoderASet;
volatile bool _RightEncoderBSet;
volatile bool _RightEncoderAPrev;
volatile bool _RightEncoderBPrev;
volatile long _RightEncoderTicks = 0;


int ParseEncoderRight(){
  if(_RightEncoderAPrev && _RightEncoderBPrev){
    if(!_RightEncoderASet && _RightEncoderBSet) return 1;
    if(_RightEncoderASet && !_RightEncoderBSet) return -1;
  }else if(!_RightEncoderAPrev && _RightEncoderBPrev) {
    if(!_RightEncoderASet && !_RightEncoderBSet) return 1;
    if(_RightEncoderASet && _RightEncoderBSet) return -1;
  }else if(!_RightEncoderAPrev && !_RightEncoderBPrev) {
    if(_RightEncoderASet && !_RightEncoderBSet) return 1;
    if(!_RightEncoderASet && _RightEncoderBSet) return -1;
  }else if(_RightEncoderAPrev && !_RightEncoderBPrev) {
    if(_RightEncoderASet && _RightEncoderBSet) return 1;
    if(!_RightEncoderASet && !_RightEncoderBSet) return -1;
  }
  return 0;
}

long getEncTicksRight()
{
  return _RightEncoderTicks;
}


// Interrupt service routines for the Right motor's quadrature encoder
void HandleRightMotorInterruptA(){
  _RightEncoderBSet = digitalRead(c_RightEncoderPinB);
  _RightEncoderASet = digitalRead(c_RightEncoderPinA);

  _RightEncoderTicks+=ParseEncoderRight();

  _RightEncoderAPrev = _RightEncoderASet;
  _RightEncoderBPrev = _RightEncoderBSet;
}

// Interrupt service routines for the right motor's quadrature encoder
void HandleRightMotorInterruptB(){
  // Test transition;
  _RightEncoderBSet = digitalRead(c_RightEncoderPinB);
  _RightEncoderASet = digitalRead(c_RightEncoderPinA);

  _RightEncoderTicks+=ParseEncoderRight();

  _RightEncoderAPrev = _RightEncoderASet;
  _RightEncoderBPrev = _RightEncoderBSet;
}


#endif
