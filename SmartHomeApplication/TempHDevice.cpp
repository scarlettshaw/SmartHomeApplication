#include "TempHDevice.h"

#include <fstream>
#include <string>
#include<vector>
#include <sstream>
#include <iostream>
#include <algorithm>


using namespace std;
TempHDevice::TempHDevice(string deviceName, bool state, string deviceType, double currenttemp, double currenthumidity, map<int,int> histData) : SHDevice(deviceName, state, deviceType), currenttemp(currenttemp), currenthumidity(currenthumidity), histData(histData){



}

void TempHDevice::viewHistoric() {
    int i = 0;
    map<int, int> histData = getHistData(); 
    map<int, int>::iterator it = histData.begin();
    cout << "-------------------------------------------------------------\n";
    while (it != histData.end()) {
        i++;

        cout << "Set" << i;
        cout << "\nHistoric Temp: " << it->first
            << "\nHistoric Humidity: " << it->second;
        cout << "\n-------------------------------------------------------------\n";
        ++it;
    }
}
//quick view displays all variables and states
void TempHDevice::quickView() {

    int uchoice;
    cout << "------------------------------------------------\n";
    cout << getName() << " is " << (getState() ? "On" : "Off") << (getState() ? " [turn off] 0" : " [turn on] 1\n") << "Current temp is " << getCurrentTemp() << "\nCurrent humidity is " << getCurrentHumidity() <<"\nPress 2 to make no changes";
    cout << "\n------------------------------------------------\n";
    cin >> uchoice;
   
    if (uchoice != 2) {
        if (uchoice == 0) {
            setState(false);
        }
        if (uchoice == 1) {
            setState(true);
        }
        if (getState() == false) {
            cout << getName() << " is " << (getState() ? "On" : "Off") << "\n" << "Current temp is " << "unavailable " << "\nCurrent humidity is" << " unavailable";
            cout << "\nThe past 2 readings are:\n";

            viewHistoric();
            cout << "------------------------------------------------\n";



        }
        else if (getState() == true) {
            cout << getName() << " is " << (getState() ? "On" : "Off") << "\n" << "Current temp is " << getCurrentTemp() << "\nCurrent humidity is " << getCurrentHumidity();
            cout << "\nThe past 2 readings are:\n";

            viewHistoric();
            cout << "------------------------------------------------\n";


        }
    }
    if (uchoice == 2) {

    }
    cout << "------------------------------------------------\n";
   
  }