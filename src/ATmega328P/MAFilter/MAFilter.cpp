
#include "MAFilter.h"

MAFilter::MAFilter(int16_t aTapeLength)
{
	isFirstLoad = true;
	firstLoadCounter = 0;

	tapeLength = aTapeLength;
	tape = (int16_t*) malloc(aTapeLength * sizeof(int16_t));

	// put zero in all positions of the tape
	for(int i = 0; i < tapeLength; i++)
		tape[i] = 0;
}

void MAFilter::addSample(int16_t sample)
{
	// check if the fist load is being performed
	// the first load doesn't care about tolerance limits
	if(isFirstLoad)
	{
		tape[firstLoadCounter] = sample;
		firstLoadCounter++;

		// flag for first load completion if counter just indexed the last element
		if(firstLoadCounter == tapeLength)
			isFirstLoad = false;
	}
	else
	{
		// shift left tape (what duplicates the last element)
		for(int i = 1; i < tapeLength; i++)
			tape[i - 1] = tape[i];

		// insert new sample in the last position
		tape[tapeLength - 1] = sample;
		
	}
}

double MAFilter::getAverage()
{
	// if it's the first load, return the last element inserted
	if(isFirstLoad)
	{
		// avoid negative indexation of tape
		if(firstLoadCounter == 0)
			return tape[firstLoadCounter];
		else
			return tape[firstLoadCounter - 1];
	}
	else
	{
		double acc = 0;

		// accumulate all samples of tape
		for(int i = 0; i < tapeLength; i++)
			acc += tape[i];

		// return the average
		return (acc * 1.0 / tapeLength);
	}
}
