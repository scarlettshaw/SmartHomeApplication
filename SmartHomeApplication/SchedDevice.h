#pragma once
#include "SHDevice.h"
#include <map>
using namespace std;
class SchedDevice : virtual public SHDevice
{
public:
	//getter and setter for attributes with quick view function and constructor based on additional attributes needed from base class
	SchedDevice(string deviceName, bool state, string deviceType, map<int, int> schedData);
	virtual void quickView();
	void setschedData(map<int, int> nschedData) { schedData = nschedData; }
	map<int, int> getschedData() const { return schedData; }
	void setSchedule();
	void viewSchedule();

private:
	map<int, int> schedData;
	double time, time2;
};

