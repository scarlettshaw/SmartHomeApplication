#include "ThermoDevice.h"

#include <fstream>
#include <string>
#include<vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include <map>

using namespace std; 


ThermoDevice::ThermoDevice(string deviceName, bool state, string deviceType, map<int, int> schedData, bool booststate) : SHDevice(deviceName, state, deviceType), SchedDevice(deviceName, state, deviceType, schedData), booststate(booststate) {


}
//quick view displays all variables and states
void ThermoDevice::quickView() {
	int uchoice;
	cout << getName() << " is " << (getState() ? "On" : "Off") << (getState() ? " [turn off] 0" : " [turn on] 1");
	cout << "\nBoost is " << (getboostState() ? "On" : "Off") << (getboostState() ? "[turn off] 2" : "[turn on] 3") <<"\nPress 4 to make no changes\n";
	
	cout << "------------------------------------------------\n";
	viewSchedule();
	cout << "------------------------------------------------\n";

	cin >> uchoice;

	if (uchoice != 4) {
		if (uchoice == 0) {

			setState(false);
		}
		if (uchoice == 1) {
			setState(true);
		}
		if (uchoice == 2) {
			setboostState(false);
		}
		if (uchoice == 3) {
			setboostState(true);
		}
		cout << "------------------------------------------------\n";
		cout << getName() << " is " << (getState() ? "On" : "Off") << "\n" << "The 1 hour boost function is " << (getboostState() ? "On" : "Off") << "\n";
	}
	if (uchoice == 4) {

	}
	
	


}