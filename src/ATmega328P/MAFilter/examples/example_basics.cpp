
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MAFilter.h"

MAFilter maf(10);

int main()
{
	int num;

	bool isRunning = true;
	while(isRunning)
	{
		scanf("%i", &num);
		maf.addSample(num);

		printf("%f\n", maf.getAverage());

		if(num < 0)
			isRunning = false;
	}
}
