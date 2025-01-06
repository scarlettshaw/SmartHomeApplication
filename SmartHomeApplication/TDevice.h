#pragma once
#include "SHDevice.h"
class TDevice : virtual public SHDevice
{
public:
	//getter and setter for attributes with quick view function and constructor based on additional attributes needed from base class
	TDevice(string deviceName, bool state, string deviceType, int timer, bool timerState);
	int getTimer() const { return timer; }
	void setTimer(const int& ntimer) { timer = ntimer; }
	bool getTimerState() const { return timerState; }
	void setTimerState(const bool& ntimerState) { timerState = ntimerState; }
    void quickView() = 0;

private:
	int timer;
	bool timerState;
};

