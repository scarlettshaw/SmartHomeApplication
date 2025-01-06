#pragma once
#include "TDevice.h"
#include "SchedDevice.h"
class SocketDevice :  public TDevice , public SchedDevice
{	//getter and setter for attributes with quick view function and constructor based on additional attributes needed from base class
public:
	SocketDevice(string deviceName, bool state, string deviceType, int timer, bool timerState, int eUse, map<int, int> schedData, map<int, int> histData);
	int geteUse() const { return eUse; }
	void seteUse(const int& neUse) { eUse = neUse; }
	void sethistData(map<int, int> nhistData) { histData = nhistData; }
	void viewHistoric();
	map<int, int> gethistData() const { return histData; }

	void quickView();
private:
	map<int, int> histData;
	int eUse;
};

