
#ifndef ENCL_H_
#define ENCL_H_
/*
*adapted from http://yameb.blogspot.com/2012/11/quadrature-encoders-in-arduino-done.html
*Quadrature Decoder
*/
#include "Arduino.h"
// #include <digitalWriteFast.h>  // library for high performance reads and writes by jrraines
                               // see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
                               // and http://code.google.com/p/digitalwritefast/

// It turns out that the regular digitalRead() calls are too slow and bring the arduino down when
// I use them in the interrupt routines while the motor runs at full speed.

// Quadrature encoders
// Left encoder

//Mega2560	2  3 21  20  19  18

#define c_LeftEncoderInterruptA 5
#define c_LeftEncoderInterruptB 4
#define c_LeftEncoderPinA 18
#define c_LeftEncoderPinB 19
#define LeftEncoderIsReversed

volatile bool _LeftEncoderASet;
volatile bool _LeftEncoderBSet;
volatile bool _LeftEncoderAPrev;
volatile bool _LeftEncoderBPrev;
volatile long _LeftEncoderTicks = 0;


int ParseEncoderLeft(){
  if(_LeftEncoderAPrev && _LeftEncoderBPrev){
    if(!_LeftEncoderASet && _LeftEncoderBSet) return 1;
    if(_LeftEncoderASet && !_LeftEncoderBSet) return -1;
  }else if(!_LeftEncoderAPrev && _LeftEncoderBPrev) {
    if(!_LeftEncoderASet && !_LeftEncoderBSet) return 1;
    if(_LeftEncoderASet && _LeftEncoderBSet) return -1;
  }else if(!_LeftEncoderAPrev && !_LeftEncoderBPrev) {
    if(_LeftEncoderASet && !_LeftEncoderBSet) return 1;
    if(!_LeftEncoderASet && _LeftEncoderBSet) return -1;
  }else if(_LeftEncoderAPrev && !_LeftEncoderBPrev) {
    if(_LeftEncoderASet && _LeftEncoderBSet) return 1;
    if(!_LeftEncoderASet && !_LeftEncoderBSet) return -1;
  }

}

long getEncTicksLeft()
{
  return _LeftEncoderTicks;
}


// Interrupt service routines for the Left motor's quadrature encoder
void HandleLeftMotorInterruptA(){
  _LeftEncoderBSet = digitalRead(c_LeftEncoderPinB);
  _LeftEncoderASet = digitalRead(c_LeftEncoderPinA);

  _LeftEncoderTicks+=ParseEncoderLeft();

  _LeftEncoderAPrev = _LeftEncoderASet;
  _LeftEncoderBPrev = _LeftEncoderBSet;
}

// Interrupt service routines for the Left motor's quadrature encoder
void HandleLeftMotorInterruptB(){
  // Test transition;
  _LeftEncoderBSet = digitalRead(c_LeftEncoderPinB);
  _LeftEncoderASet = digitalRead(c_LeftEncoderPinA);

  _LeftEncoderTicks+=ParseEncoderLeft();

  _LeftEncoderAPrev = _LeftEncoderASet;
  _LeftEncoderBPrev = _LeftEncoderBSet;
}


#endif
