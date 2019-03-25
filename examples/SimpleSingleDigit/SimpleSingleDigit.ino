#include <SerialNixieDriver.h>

/**
 SimpleSingleDigit

 This example shows a basic counter on a single Nixie Tube

 For broad compatibility; this is using software serial.

 Copyright (c) 2019 Tony Pottier, Under the MIT License
 @see https://github.com/tonyp7/SPINixieDriver
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

SerialNixieDriver driver;


void setup(){
  // Setup as software serial, no output enable pin
  driver.begin(rckPin, sckPin, dataPin, 0, false);
}

void loop(){

  // Count to 9 and mark a pause at the end. 
  for (uint8_t i = 0; i < 10; i++) {
    driver.send(i);
    delay(300);
    if(i==9) delay(700);
  }
  
}
