# HC12
HC12 cpp library for the arduino.

## Borked bits?
Powering the module on with the SET pin held to GND will force it's serial port to 9600bps, 8 data bits, no parity, 1 stop bit. Note that this only puts it into a known state, it does not set the non-volitile settings! To completely reset you must send "AT+DEFAULT".

## Commands
### Communications
* bool send(String);
  * Nothing fancy.
* unsigned short receive();
  * This should be called routinely. It reads the serial buffer and stores to a seperatue buffer.
  * When bool readReady == true, the String lastRead should be read and readReady should be set false.

### Control
* bool testModule();
  * returns 1 if OK. 0 if bad or no response.
* String getVersion();
  * returns the version information.
* void setDefaults();
  * This sets the baud rate to 9600, channel to 1, and power to 8.
* bool changeBaud(unsigned int);
  * Values: 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
  * Return: True on success, false on failure.
  * Changes the baud rate that's used locally to communicate to the device. It may also change the baud rate the devices use. Therefore if using different local baud rates, check the dota sheet to make sure the OTA rates are the same.
* bool changePower(unsigned int);
  * Values: 1-9
  * Returns: True on success, false on failure.
  * 1=.8mW, 2=1.6mW, 3=3.2mW, 4=6.3mW, 5=12mW, 6=25mW, 7=50mW, 8=100mW.
* bool changeChannel(unsigned int);
  * Values: 1-124
  * Returns: True on success, false on failure.
  * Channel stepping is 400KHz, starting at 433.4Mhz. 5 channel spacing between different networks should be used.


### Advanced Settings
* bool forwardCommand;
  * If this is set to true, commands given to the local device will also be broadcast to all listening devices for them to comply with.
  * Listening devices will repond with "RX:[command]" to verify they have received the command. Although nothing is done with this info, it will be output to your local serial log.
  * At this time, it's not set up to get a response verifying a successful command at the remote device.
* TODO:
  * changeMode(unsigned int);
  * Udps
  * Sleep

