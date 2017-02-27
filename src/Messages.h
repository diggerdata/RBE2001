
/*
 * Messages.h
 *
 *  Created on: Sep 15, 2016
 *      Author: bradmiller
 */

#ifndef MESSAGES_H_
#define MESSAGES_H_

/**
 * Handles Bluetooth messages as they are received from the Reactor Control System
 * This class keeps the current state of the field and allows your program to query it at
 * any time. The read() method is called inside the loop() of your program. It reads a
 * message and sets the internal class state based on it's contents. This happens each loop.
 * You then write methods (like isStopped(), below) that report on that state. The idea is
 * that the receipt and parsing of the messages is decoupled from your use of the state data
 * making your programs much less complex.
 *
 * You need to add code and private state variables (like stopped, below) to parse and remember
 * the RCS state. Then add methods that can be called independent of message receipt to retrieve
 * that state.
 *
 * Other things you may want to do:
 * - check is messages are addressed to your robot (or broadcast to all)
 * - handle the source and destination fields which exist for all messages
 * - add methods to determine which storage is free/used so you can ask by number
 *   rather than having to do the bit mask stuff
 */
class Messages {
public:
	typedef enum {kReserved,
		kStorageAvailability,
		kSupplyAvailability,
		kRadiationAlert,
		kStopMovement,
		kResumeMovement,
		kRobotStatus,
		kHeartbeat} MessageType;

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

	Messages();

	bool isStopped();
	void sendHeartbeat();
	bool read();
	void setup();
	unsigned char getMByte();
	void printMessage();
	char getStorageAvl();
	char getSupplyAvl();
	bool getRadAlert();
	char getRodType();

private:
	bool stopped;
	bool strTube0AVL;
	bool strTube1AVL;
	bool strTube2AVL;
	bool strTube3AVL;
	bool splyTube0AVL;
	bool splyTube1AVL;
	bool splyTube2AVL;
	bool splyTube3AVL; //all tubeXAVL variables represent the storage and supply tubes. True= contains a rod, false= empty
	bool hasSpentRod;
	bool hasNewRod;	//true= has rod, false= no rod
	unsigned char strTubeAVL;
	unsigned char splyTubeAVL;
};

#endif /* MESSAGES_H_ */
