#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <sstream>
#include "SHDevice.h"

using namespace std;

SHDevice::SHDevice(string deviceName, bool state,string deviceType) : deviceName(deviceName), state(state), deviceType(deviceType) {



}



SHDevice::SHDevice() {

}


SHDevice::~SHDevice() {

}


void SHDevice::turnOn() {
	state = true;
}
void SHDevice::turnOff() {
	state = false;
}

void SHDevice::quickView() {
	cout << deviceName << (getState() ? "On" : "Off");
}





