#ifndef L2Controller_h
#define L2Controller_h

#include <stdint.h>
#include "Common.h"

enum L2State
{
		AWAKE, SLEEP, DEEPSLEEP
};

class L2Controller
{
private:
	  static L2State currentState;

public:
		L2Controller();

		static void processACTIVEMAIN();
		static void processACTIVEPCINT0();
		static void processACTIVETMR0OVF();

		static void processINACTIVEMAIN();
		static void processINACTIVEPCINT0();
		static void processINACTIVETMR0OVF();
};

#endif
