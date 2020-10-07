
#include "HFilter.h"

HFilter::HFilter(int16_t aStateLimit, int16_t aOccLimit)
{
	stateLimit = aStateLimit;
	occLimit = aOccLimit;

	isFirstSample = true;
	lastState = STATEA;
	currentState = STATEA;
}

bool HFilter::isValidSample(int16_t aSample)
{
	// Transition Logic
	switch(currentState)
	{
		case STATEA:
			if(isFirstSample || (aSample < aTOP && aSample > aBOT))
			{
				aTOP = aSample + stateLimit;
				aBOT = aSample - stateLimit;

				isFirstSample = false;
			}
			else
			{
				bTOP = aSample + stateLimit;
				bBOT = aSample - stateLimit;

				occCounter = 0;
				lastState = currentState;
				currentState = STATET;
			}
			break;

		case STATET:
			if(lastState == STATEA)
			{
				if(aSample < bTOP && aSample > bBOT)
				{
					bTOP = aSample + stateLimit;
					bBOT = aSample - stateLimit;

					occCounter++;
					if(occCounter == occLimit)
					{
						lastState = currentState;
						currentState = STATEB;
					}
				}
				else
				{
					if(aSample < aTOP && aSample > aBOT)
					{
						currentState = lastState;
						lastState = STATET;
					}
					else
					{
						lastState = lastState;
						currentState = STATET;
					}
				}
			}
			else
			{
				if(aSample < aTOP && aSample > aBOT)
				{
					aTOP = aSample + stateLimit;
					aBOT = aSample - stateLimit;

					occCounter++;
					if(occCounter == occLimit)
					{
						lastState = currentState;
						currentState = STATEA;
					}
				}
				else
				{
					if(aSample < bTOP && aSample > bBOT)
					{
						currentState = lastState;
						lastState = STATET;
					}
					else
					{
						lastState = lastState;
						currentState = STATET;
					}
				}
			}
			break;

		case STATEB:
			if(aSample < bTOP && aSample > bBOT)
			{
				bTOP = aSample + stateLimit;
				bBOT = aSample - stateLimit;
			}
			else
			{
				aTOP = aSample + stateLimit;
				aBOT = aSample - stateLimit;

				occCounter = 0;
				lastState = currentState;
				currentState = STATET;
			}
	}

	// Output Logic
	switch(currentState)
	{
		case STATEA:

			return true;
			break;

		case STATET:

			return false;
			break;

		case STATEB:

			return true;

	}
}
