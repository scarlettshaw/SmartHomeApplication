#include "TDevice.h"
#include <fstream>
#include <string>
#include<vector>
#include <sstream>
#include <iostream>

using namespace std;
TDevice::TDevice(string deviceName, bool state, string deviceType, int timer, bool timerState) : SHDevice(deviceName, state, deviceType), timer(timer), timerState(timerState) {



}
//quick view displays all variables and states


void TDevice::quickView() {
	cout << "------------------------------------------------\n";
	cout << getName() << " is " << (getState() ? "On" : "Off") << "\n" << "Timer is " << getTimerState() << "and currently set at " << getTimer() << "hours";
	cout << "------------------------------------------------\n";
}