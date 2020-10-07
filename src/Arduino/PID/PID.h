
#ifndef PID_H
#define PID_H

class PID
{
private:
	double SP, CV, PV, lastPV, ER;
	double KP, KI, KD, P, I, D, samplingCounter, samplingLimit;

public:
	PID(double aKP, double aKI, double aKD);
	void setSP(double aSP);
	double processCV(double aPV);
};

#endif

