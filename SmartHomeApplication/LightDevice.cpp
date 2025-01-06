#include "LightDevice.h"
#include <fstream>
#include <string>
#include<vector>
#include <sstream>
#include <iostream>

using namespace std;
LightDevice::LightDevice(string deviceName, bool state, string deviceType, int timer, bool timerState, int brightness) : SHDevice(deviceName, state, deviceType),  TDevice(deviceName, state, deviceType, timer, timerState) , brightness(brightness) {



}
//quick view displays all variables and states
void LightDevice::quickView() {
	
	int uchoice;



	cout << getName() << " is " << (getState() ? "On" : "Off") << (getState() ? " [turn off] 0" : " [turn on] 1") << "\nSleep Timer is " << (getState() ? "On" : "Off") << (getState() ? " [turn off] 2" : " [turn on] 3");
	cout << "\nTimer is set at " << getTimer() << " hours" << "\n" << "Brightness is set to " << getBrightness() << "\n" <<"Press 4 to make no changes";
	cout << "\n------------------------------------------------\n";
		//one click controls
		cin >> uchoice;
		if (uchoice != 4) {
			if (uchoice == 0) {
				setState(false);
			}
			if (uchoice == 1) {
				setState(true);
			}
			if (uchoice == 2) {
				setTimerState(false);
			}
			if (uchoice == 3) {
				setTimerState(true);
			}
		}
		
		else if (uchoice == 4) {
			
		}
		

		cout << "------------------------------------------------\n";
		//checks for the user input, changes the attribute value accordingly
}