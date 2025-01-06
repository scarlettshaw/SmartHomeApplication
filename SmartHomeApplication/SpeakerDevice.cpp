#include "SpeakerDevice.h"
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <sstream>

using namespace std;
SpeakerDevice::SpeakerDevice(string deviceName, bool state, string deviceType, int volume) : SHDevice(deviceName, state, deviceType), volume(volume) {



}
//quick view displays all variables and states

void SpeakerDevice::quickView() {
	int uchoice;
	cout << "------------------------------------------------\n";
	cout << getName() << " is " << (getState() ? "Playing" : "Paused") << (getState() ? " [turn off] 0" : " [turn on] 1") << "\nVolume is set at " << getVolume() <<"\nPress 2 to make no changes";
	cout << "\n------------------------------------------------\n";
	cin >> uchoice;
	if (uchoice != 2) {


		if (uchoice == 0) {
			setState(false);
		}
		if (uchoice == 1) {
			setState(true);
		}



		cout << "------------------------------------------------\n";
		cout << getName() << " is now " << (getState() ? "Playing" : "Paused") << "\n";
		cout << "------------------------------------------------\n";

	}



	
	
}