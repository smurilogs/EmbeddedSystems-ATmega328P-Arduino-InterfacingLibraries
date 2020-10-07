
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "PID.h"

PID pid(1.0, 0.0, 0.0);

int main()
{
	int num;

	bool isRunning = true;
	while(isRunning)
	{
		scanf("%i", &num);

		if(num == 0)
			isRunning = false;
		else
		{
			pid.setSP(num);
			//int CV = pid.processCV();
			//printf("%f\n", );
		}
	}

	return 0;
}