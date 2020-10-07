
#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <avr/io.h>

class RotaryEncoder
{
private:
	int32_t counter;
	uint8_t lastALevel;

	uint8_t acquireALevel();
	uint8_t acquireBLevel();

public:
	bool ENABLED;

	RotaryEncoder();
	void init();

 	uint8_t process();
	int32_t getCounter();
	void clearCounter();
};

#endif
