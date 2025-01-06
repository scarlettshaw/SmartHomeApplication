#pragma once
#include <string>
#include<vector>
using namespace std;

class SHDevice {
	//getter and setter for attributes with quick view function and constructor based on additional attributes needed from base class
public:
	SHDevice();
	SHDevice(string deviceName, bool state, string deviceType);
	~SHDevice();

	void turnOn();
	void turnOff();
	virtual void quickView();

	bool getState() const { return state; }
	void setState(const bool& nstate) {state = nstate;}

	string getName() const {return deviceName;}
	void setName(const string& ndeviceName) { deviceName = ndeviceName; }

	string getdeviceType() const { return deviceType; }
	void setdeviceType(const string& ndeviceType) { deviceType = ndeviceType; }

	

private:
	string deviceName;
	string deviceType;
	bool state;


};




