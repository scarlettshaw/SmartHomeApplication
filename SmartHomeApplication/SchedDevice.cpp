#include "SchedDevice.h"
#include <map>
#include <fstream>
#include <string>
#include<vector>
#include <sstream>
#include <iostream>

using namespace std;

SchedDevice::SchedDevice(string deviceName, bool state, string deviceType, map<int, int> schedData) : SHDevice(deviceName, state, deviceType), schedData(schedData) {



}
//quick view displays all variables and states


void SchedDevice::setSchedule() {
	
	cout << "Enter Schedule 1 start time";
	int time1;

	cin >> time1;
	cout << "Enter Schedule 1 end time";
	int time2;
	cin >> time2;
	cout << "Enter Schedule 2 start time";
	int time3;
	cin >> time3;
	cout << "Enter Schedule 2 end time";
	int time4;
	cin >> time4;
	schedData.clear();
	schedData.insert({ time1, time2 });
	schedData.insert({ time3, time4 });
	setschedData(schedData);

	cout << "-------------------------------------------------------------\n";
	int i = 0;
	map<int, int>::iterator it = schedData.begin();
	while (it != schedData.end()) {
		i++;
		cout << "New Schedule " << i;
		cout << " Runs from: " << it->first << " HOURS";
		cout << " Till: " << it->second << " HOURS\n";
		it++;
	}
}
void SchedDevice::quickView() {
	cout << "------------------------------------------------\n";
	cout << getName() << " is " << (getState() ? "On" : "Off") << "\n";
	cout << "\nThe past 2 readings are:\n";
	viewSchedule();
	cout << "------------------------------------------------\n";

}

void SchedDevice::viewSchedule(){

	int i = 0;
	map<int, int> schedData = getschedData();
	map<int, int>::iterator it = schedData.begin();
	cout << "-------------------------------------------------------------\n";
	while (it != schedData.end()) {
		i++;
		cout << "Schedule " << i;
		cout << " Runs from: " << it->first << " HOURS";
		cout << " Till: " << it->second << " HOURS\n";
		it++;
	}
}
