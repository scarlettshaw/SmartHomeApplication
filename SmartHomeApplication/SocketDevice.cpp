#include "SocketDevice.h"

#include <fstream>
#include <string>
#include<vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

SocketDevice::SocketDevice(string deviceName, bool state, string deviceType, int timer, bool timerState, int eUse, map<int, int> schedData, map<int, int> histData) :SHDevice(deviceName, state, deviceType), TDevice(deviceName, state, deviceType, timer, timerState), SchedDevice(deviceName, state, deviceType, schedData), eUse(eUse), histData(histData) {

}
//quick view displays all variables and states

void SocketDevice::viewHistoric() {
	int i = 4;
	map<int, int> histData = gethistData();
	map<int, int>::iterator it = histData.begin();
	cout << "-------------------------------------------------------------\n";
	while (it != histData.end()) {

		cout << "Energy usage " << i << "months(s) ago: " << it->first << "watts\n";
		i--;
		cout << "Energy usage " << i << "months(s) ago: " << it->second << "watts\n";
		i--;
		it++;

	}


	cout << "-------------------------------------------------------------\n";
}
void SocketDevice::quickView() {
	int uchoice;
	cout << getName() << " is " << (getState() ? "On" : "Off") << (getState() ? " [turn off] 0" : " [turn on] 1") << "\n" << getName() << " timer is " << (getTimerState() ? "On" : "Off") << (getTimerState() ? " [turn off] 2" : " [turn on] 3") << "\nCurrent energy usage is " << geteUse() << " Watts\nPress 4 to make no changes\n";
	
	viewSchedule();


	cin >> uchoice;
	if (uchoice != 4) {


		if (uchoice == 0) {

			setState(false);
		}
		if (uchoice == 1) {
			setState(true);
		}
		if (uchoice == 2) {

			setState(false);
		}
		if (uchoice == 3) {
			setState(true);
		}

		cout << "------------------------------------------------\n";
		cout << TDevice::getName() << " is " << (TDevice::getState() ? "On" : "Off") << "\n" << "Timer is " << (getTimerState() ? "On" : "Off") << "\n";

	}

	if (uchoice == 4) {

	}

    
}