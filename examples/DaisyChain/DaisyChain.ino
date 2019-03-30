#include <SerialNixieDriver.h>

/**
 DaisyChain

 This example shows how to use the driver with a daisy chain

 For broad compatibility; this is using software serial.

 Copyright (c) 2019 Tony Pottier, Under the MIT License
 @see https://github.com/tonyp7/SerialNixieDriver
 */


/**
 * Please plug the following pin:
 *  Pin 10 to the RCK pin on the board
 *  Pin 13 to the SCK pin on the board
 *  Pin 11 to the DIN (data in) pin on the board
 *  Output Enable should be tied to Ground
 */
int rckPin = 10;
int sckPin = 13;
int dataPin = 11;

// The nixie tube driver declaration
SerialNixieDriver driver;

// Array used to hold our numbers that will be displayed on the tube
uint8_t data[] = {6, 7, 8, 9};

// The nunber of tubes used in the daisy chain
const uint8_t NB_TUBES = 4;

void setup(){
  // Setup as software serial, no output enable pin
  driver.begin(rckPin, sckPin, dataPin);
  
  //display "6 7 8 9" on a daisy chain of 4 tubes
  driver.send(data, NB_TUBES);
}

void loop(){

}
