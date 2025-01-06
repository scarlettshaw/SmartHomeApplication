#pragma once
#include "SchedDevice.h"
class RadiatorDevice : public SchedDevice
{
public:
	//getter and setter for attributes with quick view function and constructor based on additional attributes needed from base class
	RadiatorDevice(string deviceName, bool state, string deviceType, map<int, int> schedData, double temp);
	double getTemp() const { return temp; }
	void setTemp(const double& ntemp) { temp = ntemp; }
	void quickView();

private:
	double temp;
};

