
#ifndef MAFilter_h
#define MAFilter_h

#include <stdint.h>
#include <stdlib.h>

class MAFilter
{
private:
	bool isFirstLoad;
	int16_t firstLoadCounter;

	int16_t *tape;
	int16_t tapeLength;

public:
	MAFilter(int16_t aTapeLength);
	void addSample(int16_t sample);
	double getAverage();
};

#endif
