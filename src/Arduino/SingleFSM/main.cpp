#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>

#include "Common.h"
#include "L1Controller.h"


ISR(PCINT0_vect)
{
		L1Controller::processPCINT0();
}

ISR(TIMER0_OVF_vect)
{
		L1Controller::processTMR0OVF();
}

int main()
{
		sei();
		while(1)
				L1Controller::processMAIN();
}
