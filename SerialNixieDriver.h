/*
Copyright (c) 2019 Tony Pottier

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

@file SerialNixieDriver.h
@author Tony Pottier
@brief Arduino library to easily communicated with daisy-chained Nixie tubes.

@see https://idyl.io
@see https://github.com/tonyp7/SerialNixieDriver
*/


#ifndef SerialNixieDriver_h
#define SerialNixieDriver_h

#include <SPI.h>


class SerialNixieDriver {
  public:
	SerialNixieDriver();
	~SerialNixieDriver();
	
	/** @brief Initialize the driver
	*	this should be called in the "setup" part of an Arduino program or outside a loop otherwise.
	*	If hardwareSPI is set to true, the pins specified must be the correct SPI pins of the board being used.
	*	Output Enable is optional and can be set to 0 if not used.
	*	@param rckPin The pin used as a "chip select". Technically the latch register clock.
	*	@param clkPin The pin used for serial clock.
	*	@param dataPin The pin used to transmit data. In the case of hardware SPI this is the MOSI pin.
	*	@param useHardwareSPI If set to true, Arduino SPI library will be used. Otherwise, software serial will be used via the shiftOut function.
	*/
	void begin( int rckPin, int clkPin, int dataPin, int outputEnablePin = 0, bool useHardwareSPI = true);
	
	
	/** @brief Enable/disable output 
	*	Please note that as Output Enable pin uses reverse logic, setting "true" will actually pull the output enable pin LOW.
	*/
	void outputEnable( bool value );
	
	/** @brief kills the driver. If software serial is used this servers no purpose */
	void end();
	
	/** @brief Sends an array of data over daisy-chained nixie tube
	*	@param data an array containing numbers to display
	*/
	void send(const uint8_t *data);
	
	/** @brief Sends a single digit over to a nixie tube
	*	@param data the digit value to display
	*/
	void send(const uint8_t data);

  private:
	bool _useHardwareSPI = true;
	int _rckPin = 0;
	int _clkPin = 0;
	int _dataPin = 0;
	int _outputEnablePin = 0;
	uint16_t decode(uint8_t digit);
	void pushData(const uint8_t data);
};
#endif