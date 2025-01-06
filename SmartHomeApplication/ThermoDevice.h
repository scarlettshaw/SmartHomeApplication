#pragma once
#include "SchedDevice.h"
class ThermoDevice :  public SchedDevice
{
public:
	//getter and setter for attributes with quick view function and constructor based on additional attributes needed from base class
	ThermoDevice(string deviceName, bool state, string deviceType, map<int, int> schedData, bool booststate);
	void quickView();
	bool getboostState() const { return booststate; }
	void setboostState(const bool& nbooststate) { booststate = nbooststate; }

private:
	const int boost = 1;
	bool booststate;
};

