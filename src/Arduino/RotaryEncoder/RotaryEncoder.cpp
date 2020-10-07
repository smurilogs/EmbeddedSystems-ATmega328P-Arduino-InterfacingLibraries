
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder()
{

}

//void RotaryEncoder::init(uint8_t aABank, uint8_t aABit, uint8_t aBBank, uint8_t aBBit)
void RotaryEncoder::init()
{
    ENABLED = false;

    // Makes sure counter will start from zero
    counter = 0;

    // Set chosen pins as input
    DDRB &= ~(1 << 2) & ~(1 << 1);

    // Gives an initial level condition to lastAlevel variable
    lastALevel = acquireALevel();
}

// checks if the pin chosen as A is HIGH
uint8_t RotaryEncoder::acquireALevel()
{

	if(PINB & (1 << 1))
    	return 1;
    else
    	return 0;
}

// checks if the pin chosen as B is HIGH
uint8_t RotaryEncoder::acquireBLevel()
{
	if(PINB & (1 << 2))
    	return 1;
    else
    	return 0;
}

// Sweeps chosen A and B pins to identify turns, registering this in the variable "counter"
// Returns differen than 0 if a turn was caught, allowing to use that to trigger code blocks
uint8_t RotaryEncoder::process()
{
  // Holds current A level
  uint8_t ALevel = acquireALevel();

  // If the last A level registered is different than current, a pulse is detected
	if(lastALevel != ALevel)
  {
    // If, in the pulse detected, A and B are in different levels...
    if(acquireBLevel() != ALevel)
		{
      // Makes current A level be the last A level
      lastALevel = ALevel;

      // Decrements counter
      counter--;

      // Returns an extra indication that it was a CCW turn
      return -1;
    }
		else
    {
      // Makes current A level be the last A level
      lastALevel = ALevel;

      // Increments counter
      counter++;

      // Returns an extra indication that it was a CW turn
      return 1;
    }
  }
	else  // If last A level and current A level are in the same state, there wasn't pulse
  {
    // Makes current A level be the last A level
    lastALevel = ALevel;

    // Returns an extra indication that there wasn't turn
    return 0;
  }
}

// Gets counter value
int32_t RotaryEncoder::getCounter()
{
	return counter;
}

// Sets counter as 0, cam be used in the main code to avoid eventual variable overflow
void RotaryEncoder::clearCounter()
{
	counter = 0;
}
