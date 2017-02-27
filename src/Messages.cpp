/*
 * Messages.cpp
 *
 *  Created on: Sep 15, 2016
 *      Author: bradmiller
 */
#include "Arduino.h"
#include "Messages.h"
#include "BTComms.h"
#include "RobotMap.h"

BTComms comms;

/**
 * Constuctor
 * Initialize everything here when the class is created
 * Note: you cannot call methods that depend on other classes having already been created
 */
Messages::Messages() {
	stopped = false;
}

/**
 * Setup class code that is called from the Arduino sketch setup() function. This doesn't
 * get called until all the other classes have been created.
 */
void Messages::setup() {
	comms.setup();
}

/**
 * Check if the field is currently in the "stop" state
 * @returns bool value that is true if the robot should be stopped
 */
bool Messages::isStopped() {
	return stopped;
}

/**
 * Send a heartbeat message to the field to let it know that your code is alive
 * This should be called by your robot program periodically, say once per second. This
 * timing can easily be done in the loop() function of your program.
 */
void Messages::sendHeartbeat() {
	comms.writeMessage(kHeartbeat, 0x0a, 0x00);
}

/**
 * Print message for debugging
 * This method prints the message as a string of hex numbers strictly for debugging
 * purposes and is not required to be called for any other purpose.
 */
void Messages::printMessage() {
    for (int i = 0; i < comms.getMessageLength(); i++) {
      Serial.print(comms.getMessageByte(i), HEX);
      Serial.print(" ");
    }
}


unsigned char Messages::getMByte() {

	return comms.getMessageByte(0);
}

/**
 * Read messages from the Bluetooth serial connection
 * This method should be called from the loop() function in your arduino code. It will check
 * to see if the lower level comms object has received a complete message, and run the appropriate
 * code to handle the message type. This should just save the state of the message inside this class
 * inside member variables. Then add getters/setters to retrieve the status from your program.
 */
bool Messages::read() {

	if (comms.read()) {
		Serial.println("Test");

		if(comms.getMessageByte(src) != 0x00) {return false;}
		if(comms.getMessageByte(dest) != 00 || comms.getMessageByte(dest) != 13) {return false;}

		switch (comms.getMessageByte(type)) {
			case kStorageAvailability:
				strTube0AVL= (comms.getMessageByte(0) & BIT0);
				strTube1AVL= (comms.getMessageByte(0) & BIT1);
				strTube2AVL= (comms.getMessageByte(0) & BIT2);
				strTube3AVL= (comms.getMessageByte(0) & BIT3);
				break;

			case kSupplyAvailability:
				splyTube0AVL= (comms.getMessageByte(0) & BIT0);
				splyTube1AVL= (comms.getMessageByte(0) & BIT1);
				splyTube2AVL= (comms.getMessageByte(0) & BIT2);
				splyTube3AVL= (comms.getMessageByte(0) & BIT3);
				break;

			case kRadiationAlert:
				if(comms.getMessageByte(0) == 0x2C)
					hasSpentRod= true;
				else
					hasSpentRod= false;

				if(comms.getMessageByte(0) == 0xFF)
					hasNewRod= true;
				else
					hasNewRod= false;
				break;

			case kStopMovement:
				//stopped = true;
				//Serial.print("stopped");
				break;

			case kResumeMovement:
				//stopped = false;
				//Serial.print("resumed");
				break;

			case kRobotStatus:
				break;

			case kHeartbeat:
				break;

			default:
			  //Serial.print("defaulted");
				break;
		}
		//Serial.print("read");
		return true;
	}
	return false;
}

bool Messages::getStorageAvl() {
		
}

bool Messages::getSupplyAvl() {

}

bool Messages::getRadAlert() {
	if(hasNewRod || hasSpentRod)
		return true;
}

char Messages::getRodType() {	//returns n for new rod, s for spent, e for error
	if(hasNewRod && !hasSpentRod)
		return 'n';
	else if(!hasNewRod && hasSpentRod)
		return 's';
	else
		return 'e';
}
