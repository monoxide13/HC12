#ifndef HC12H
#define HC12H
#include "Arduino.h"

#define HC12_BAUD_1200 1200     // "AT+B1200" OTA baud 5000bps
#define HC12_BAUD_2400 2400     // "AT+B2400" OTA baud 5000bps
#define HC12_BAUD_4800 4800     // "AT+B4800" OTA baud 15000bps
#define HC12_BAUD_9600 9600     // "AT+B9600" OTA baud 15000bps
#define HC12_BAUD_19200 19200   // "AT+B19200" OTA baud 58000bps
#define HC12_BAUD_38400 38400   // "AT+B38400" OTA baud 58000bps
#define HC12_BAUD_57600 57600   // "AT+B57600" OTA baud 236000bps
#define HC12_BAUD_115200 115200 // "AT+B115200" OTA baud 236000bps

#define HC12_POWER_1 1 // "AT+P1" -1dBm .8mW
#define HC12_POWER_2 2 // "AT+P2" 2dBm 1.6mW
#define HC12_POWER_3 3 // "AT+P3" 5dBm 3.2mW
#define HC12_POWER_4 4 // "AT+P4" 8dBm 6.3mW
#define HC12_POWER_5 5 // "AT+P5" 11dBm 12mW
#define HC12_POWER_6 6 // "AT+P6" 14dBm 25mW
#define HC12_POWER_7 7 // "AT+P7" 17dBm 50mW
#define HC12_POWER_8 8 // "AT+P8" 20dBm 100mW
#define HC12_BUFFERSIZE 32

/* Functions still to add:
*    Get parameters: AT+Ry, AT+Rx
*    Sleep: AT+SLEEP
*    Mode: AT+FUx
*/

	
class HC12{
	public:
	HC12(HardwareSerial*, unsigned short);
	bool init();
	bool send(String);
	unsigned int receive();
	bool testModule();
	String getVersion();
	void setDefaults();
	bool changeBaud(unsigned int);
	bool changePower(unsigned int);
	bool changeChannel(unsigned int);
	String lastRead;
	bool forwardCommand;
	bool readReady;
	
	private:
	HardwareSerial* serial;
	String command(String);
	const unsigned short commandPin;
	unsigned int power;
	unsigned int channel;
	unsigned int baud;
	char SerialByteIn;                              // Temporary variable
	char HC12ByteIn;                                // Temporary variable
	String HC12ReadBuffer;                     // Read/Write Buffer 1 for HC12
	String SerialReadBuffer;                   // Read/Write Buffer 2 for Serial
	boolean SerialEnd;                      // Flag to indicate End of Serial String
	boolean HC12End;                        // Flag to indiacte End of HC12 String
	boolean commandMode;                    // Send AT commands
	boolean sleeping;
};

#endif
