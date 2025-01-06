#pragma once
#include "SHDevice.h"
class SpeakerDevice : public SHDevice
{
public:
	//getter and setter for attributes with quick view function and constructor based on additional attributes needed from base class
	SpeakerDevice(string deviceName, bool state, string deviceType, int volume);
	int getVolume() const { return volume; }
	void setVolume(const int& nvolume) { volume = nvolume; }
	void quickView();

private:
	int volume;
};

