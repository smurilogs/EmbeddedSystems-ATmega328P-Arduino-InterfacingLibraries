
#ifndef HFILTER_H
#define HFILTER_H

#include <stdint.h>

enum State 
{  
	STATEA, STATET, STATEB
};

class HFilter
{
private:
	State currentState;
	State lastState;
	int16_t stateLimit;
    int16_t occLimit, occCounter;
    int16_t aTOP, aBOT;
    int16_t bTOP, bBOT;
	bool isFirstSample;

public:
	HFilter(int16_t aStateLimit, int16_t aOccLimit);
	bool isValidSample(int16_t aSample);	
};

#endif