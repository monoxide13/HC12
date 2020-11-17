#include "HC12.hpp"
#include "Arduino.h"

HC12::HC12(HardwareSerial* serialIn, unsigned short commandPinIn) : serial(serialIn), commandPin(commandPinIn) {
	forwardCommand = false;
	readReady = false;
	sleeping = false;
	HC12ReadBuffer.reserve(HC12_BUFFERSIZE);
	lastRead.reserve(HC12_BUFFERSIZE);
};

bool HC12::init(){
	serial->begin(9600);
	HC12ReadBuffer = "";                     // Read/Write Buffer 1 for HC12
	SerialReadBuffer = "";                   // Read/Write Buffer 2 for Serial
	SerialEnd = false;                      // Flag to indicate End of Serial String
	HC12End = false;                        // Flag to indiacte End of HC12 String
	commandMode = false;                    // Send AT commands
	lastRead = "";
};

String HC12::command(String command){
	if(forwardCommand){
		send(command);
		serial->flush();
	}
	digitalWrite(commandPin, LOW);
	delay(50);
	serial->print(command);
	String retVal = serial->readString();
	delay(100);
	digitalWrite(commandPin, HIGH);
	return retVal;
};

bool HC12::send(String input){
	if(!sleeping){
		serial->println(input);
		return 1;
	}
	return 0;
};

unsigned int HC12::receive(){
	int retVal=0;
	while (serial->available()) {
	  HC12ByteIn = serial->read();
	  if (HC12ByteIn == '\n'){
		  if (forwardCommand && HC12ReadBuffer.startsWith("AT+")) {      // Check to see if a command is received from remote
		  	serial->print("RX:"+HC12ReadBuffer);
			serial->flush();
			digitalWrite(commandPin, LOW);
			delay(50);
			serial->print(SerialReadBuffer);
			serial->flush();
			delay(50);
			digitalWrite(commandPin, HIGH);
			delay(100);
		  } else { // Not a local command. Save it.
				lastRead = HC12ReadBuffer;
				readReady = true;
		  }
		  HC12ReadBuffer = "";
	  }
	  else
		HC12ReadBuffer += char(HC12ByteIn);
		++retVal;
	}
	return retVal;
};

bool HC12::testModule(){
	if(command("AT") == "OK\n")
		return 1;
	return 0;
};

String HC12::getVersion(){
	return command("AT+V");
};

void HC12::setDefaults(){
	command("AT+DEFAULT\n");
};

bool HC12::changeBaud(unsigned int newBaud){
	// TODO: Check if successful by comparing to "OK+B19200);
	String retVal;
	switch (newBaud){
		case 1200:
			command(String("AT+B1200"));
			break;
		case 2400:
			command(String("AT+B2400"));
			break;
		case 4800:
			command(String("AT+B4800"));
			break;
		case 9600:
			command(String("AT+B9600"));
			break;
		case 19200:
			command(String("AT+B19200"));
			break;
		case 38400:
			command(String("AT+B38400"));
			break;
		case 57600:
			command(String("AT+B57600"));
			break;
		case 115200:
			command(String("AT+B115200"));
			break;
		default:
			return 0;
	}
};

bool HC12::changePower(unsigned int in){
	// TODO
};

bool HC12::changeChannel(unsigned int newChannel){
	if(newChannel>0 && newChannel<128){
		command(String("AT+C" + newChannel));
	}
};
