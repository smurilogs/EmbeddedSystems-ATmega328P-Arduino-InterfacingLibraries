
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "HFilter.h"

HFilter hf(5, 3);

int main()
{
	int num;

	bool isRunning = true;
	while(isRunning)
	{
		scanf("%i", &num);

		if(hf.isValidSample(num))
			printf("true\n");
		else
			printf("false\n");

		if(num < 0)
			isRunning = false;
	}
}
