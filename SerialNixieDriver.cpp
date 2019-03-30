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

@file SerialNixieDriver.cpp
@author Tony Pottier
@brief Arduino library to easily communicated with daisy-chained Nixie tubes.

@see https://idyl.io
@see https://github.com/tonyp7/SerialNixieDriver
*/


#include "SerialNixieDriver.h"


SerialNixieDriver::SerialNixieDriver() {

}

SerialNixieDriver::~SerialNixieDriver() {
	this->end();
}



void SerialNixieDriver::outputEnable(bool value){
	if(this->_outputEnablePin){
		if(value){
			digitalWrite(this->_outputEnablePin, LOW);
		}
		else{
			digitalWrite(this->_outputEnablePin, HIGH);
		}
	}
}

void SerialNixieDriver::begin( int rckPin, int clkPin, int dataPin, int outputEnablePin, bool useHardwareSPI ){
	
	this->_useHardwareSPI = useHardwareSPI;
	this->_clkPin = clkPin;
	this->_rckPin = rckPin;
	this->_dataPin = dataPin;
	this->_outputEnablePin = outputEnablePin;
	
	if(outputEnablePin){
		pinMode(outputEnablePin, OUTPUT);
		digitalWrite(outputEnablePin, HIGH);
	}
	
	pinMode(clkPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(rckPin, OUTPUT);
	digitalWrite(rckPin, LOW);
	digitalWrite(dataPin, LOW);
	digitalWrite(clkPin, LOW);
	
	if(useHardwareSPI){
		SPI.begin();
	}
	
	
	
}


uint16_t SerialNixieDriver::decode(const uint8_t digit){
	if(digit < 10){
		return ((uint16_t)1)<<digit;
	}
	else{
		return (uint16_t)0x0000;
	}
}


void SerialNixieDriver::pushData(const uint8_t data){
	if(this->_useHardwareSPI){
		SPI.transfer16(this->decode(data));
	}
	else{
		uint16_t bcd = this->decode(data);
		shiftOut(this->_dataPin, this->_clkPin, MSBFIRST, bcd >> 8);
		shiftOut(this->_dataPin, this->_clkPin, MSBFIRST, bcd & 0xFF);
	}
}


void SerialNixieDriver::send(const uint8_t *data, const uint8_t size){
	if(data && size){
		digitalWrite(this->_rckPin, LOW);
		for(int i = size-1; i >= 0; i--){
			this->pushData(data[i]);
		}
		digitalWrite(this->_rckPin, HIGH);
	}
}

void SerialNixieDriver::send(const uint8_t data){
	digitalWrite(this->_rckPin, LOW);
	this->pushData(data);
	digitalWrite(this->_rckPin, HIGH);
}

void SerialNixieDriver::end(){
	if(this->_useHardwareSPI){
		SPI.end();
	}
}
	