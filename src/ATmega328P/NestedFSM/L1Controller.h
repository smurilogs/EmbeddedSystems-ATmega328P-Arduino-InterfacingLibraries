#ifndef L1Controller_h
#define L1Controller_h

#include <stdint.h>
#include "Common.h"
#include "L2Controller.h"

enum L1State
{
		ACTIVE, INACTIVE
};

class L1Controller
{
private:
	  static L1State currentState;

public:
		L1Controller();
		static void processMAIN();
		static void processPCINT0();
		static void processTMR0OVF();
};

#endif
