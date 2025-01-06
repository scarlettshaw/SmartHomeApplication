#include "RadiatorDevice.h"
#include <fstream>
#include <string>
#include<vector>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
RadiatorDevice::RadiatorDevice(string deviceName, bool state, string deviceType, map<int, int> schedData, double temp) :SHDevice(deviceName, state, deviceType), SchedDevice(deviceName, state, deviceType, schedData), temp(temp) {



}
//quick view displays all variables and states

void RadiatorDevice::quickView() {
	int uchoice;
	cout << getName() << " is " << (getState() ? "On" : "Off") << (getState() ? " [turn off] 0" : " [turn on] 1") << "\nTemperature is " << getTemp()<<"\nPress 2 to make no changes\n";

	cout << "------------------------------------------------\n";

	viewSchedule();
	cout << "------------------------------------------------\n";

	cin >> uchoice;
	if (uchoice != 2) {


		if (uchoice == 0) {

			setState(false);
		}
		if (uchoice == 1) {
			setState(true);
		}

		cout << "------------------------------------------------\n";

		cout << getName() << " is " << (getState() ? "On" : "Off") << "\n" << "Current temp is " << getTemp() << "\n";

		cout << "------------------------------------------------\n";
	}
	if (uchoice == 2) {

	}




}