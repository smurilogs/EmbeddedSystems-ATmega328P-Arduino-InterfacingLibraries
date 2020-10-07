
#include "PID.h"

PID::PID(double aKP, double aKI, double aKD)
{
	KP = aKP;
	KI = aKI;
	KD = aKD;

	lastPV = 0;
	SP = 0;
    I = 0;
    samplingLimit = 1000;
    samplingCounter = 0;
}

void PID::setSP(double aSP)
{
	SP = aSP;
}

double PID::processCV(double aPV)
{
	PV = aPV;
	ER = SP - PV;

	P = KP * ER;
	I = I + (KI * ER);
	D = KD * (PV - lastPV); 

	CV = P + I + D;

	lastPV = PV;			
	samplingCounter++;
	if(samplingCounter == samplingLimit)
	{
		I = 0;
		samplingCounter = 0;
	}	

	return CV;
}