#ifndef SPINixieDriver_h
#define SPINixieDriver_h

#include <SPI.h>

class SPINixieDriver {
  public:
	SPINixieDriver();
	~SPINixieDriver();
	void begin( int rckPin, int clkPin, int dataPin, int outputEnablePin, bool useHardwareSPI );
	void outputEnable( bool value );
	void end();
	
	/** @brief Sends an array of data over daisy-chained IN-12
	*/
	void send(const uint8_t *data);
	void send(const uint8_t data);

  private:
	bool _useHardwareSPI = true;
	int _rckPin = 0;
	int _clkPin = 0;
	int _dataPin = 0;
	int _outputEnablePin = 0;
	uint16_t decode(uint8_t digit);
};
#endif