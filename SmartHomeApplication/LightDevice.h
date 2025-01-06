#pragma once
#include "TDevice.h"
class LightDevice : public TDevice
{
public:
	//getter and setter for attributes with quick view function and constructor based on additional attributes needed from base class
	LightDevice(string deviceName, bool state, string deviceType, int timer, bool timerState, int brightness);
	int getBrightness() const { return brightness; }
	void setBrightness(const int& nbrightness) { brightness = nbrightness; }
	void quickView();
private:
	int brightness;
};

