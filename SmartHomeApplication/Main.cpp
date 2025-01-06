
#include <iostream>
#include <vector>
#include "SHDevice.h"
#include "SpeakerDevice.h"
#include "LightDevice.h"
#include "TempHDevice.h"
#include "SchedDevice.h"
#include "ThermoDevice.h"
#include "RadiatorDevice.h"
#include "SocketDevice.h"
#include <algorithm>
#include <crtdbg.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iomanip> 
#include <random>
#include <conio.h>
using namespace std;

random_device rd;
mt19937 gen(rd());

void mainMenu(vector<SHDevice*> homeDevices);
/*for clarity, my hierachy is as follows, the base class is SHDevice, 4 classes inherit from this, TDevice and SchedDevice include attributes to be commonly used across lower classes 
they inherit SHDevice virtually.THSensor and Speaker directly inherit as they have attributes that are not common across my hierachy. Light inherits from TDevice, 
Socket inherits from both TDevice and SchedDevice,and Thermostat and Radiator inherit from SchedDevice*/

bool nav(vector<SHDevice*> homeDevices) {//function for asking user to return to main menu after changing features of a device
	int choice;
	cout << "Would you like to go back to the main menu or keep changing this device? 0/1";
	cin >> choice;
	if (choice == 0) {
		return false;
	}
	else {
		return true;
	}

}


bool nav2(vector<SHDevice*> homeDevices) {//function for asking user to return to main menu after viewing features of a device
	int choice;
	cout << "Would you like to go back to the main menu or keep viewing this device? 0/1";
	cin >> choice;
	if (choice == 0) {
		return false;
	}
	else {
		return true;
	}

}


bool nav3(vector<SHDevice*> homeDevices) {//function for asking user to return to main menu without offering another option
	int choice;
	cout << "Press 1 to go back to the main menu";
	cin >> choice;
	if (choice == 1) {
		return true;
	}
	else {
		return false;
	}
	
}


//https://www.w3schools.com/cpp/cpp_files.asp
//from this source, i learnt how to read a file using ifstream, and how to use the getline function to read line by line and store the data as a variable
vector<SHDevice*> readFile(vector <SHDevice*> homeDevices) {//function for reading file and pushing an object created from file values into a vector
	string textFile;
	ifstream readFile("alldevices.txt");//reads file in my resource files


	while (getline(readFile, textFile)) {
		stringstream ss(textFile);
		string ndeviceType;//to store new device type
		string ndeviceName;//to store new device name


		getline(ss, ndeviceType, '|');//every value is separated by a | until the end of the line
		
	     if (ndeviceType == "Speaker") {//checking what device type the device belongs to

			getline(ss, ndeviceName, '|'); //stores the value up to the separator as the deviceName
			string stateStr;
			getline(ss, stateStr, '|'); 
			bool nstate;
			string volumestr;
			getline(ss, volumestr, '|');
			int nvolume = stoi(volumestr);//as the object needs an interger I convert it from a string
		
			if (stateStr == "TRUE") {
				nstate = true;//formats the state from the file into a bool value that I can use in the object
			}
			else {
				nstate = false;
			}

			//each line is formatted so the line can be read in a certain order for certain variables
			homeDevices.push_back(new SpeakerDevice(ndeviceName, nstate, ndeviceType, nvolume));//pushes back the object to a class
		}
		else if (ndeviceType == "LightDevice") {
			
			getline(ss, ndeviceName, '|'); 
			string stateStr;
			getline(ss, stateStr, '|'); 
			bool nstate;
			bool ntstate;
			string timerstate;
			getline(ss, timerstate, '|'); 
			string timernum;
			getline(ss, timernum, '|');
			int timernumint = stoi(timernum);
			string brightnessnum;
			getline(ss, brightnessnum, '|');
			int brightnessnumint = stoi(brightnessnum);
		
			if (stateStr == "TRUE") {
				nstate = true;
			}
			else {
				nstate = false;
			}

			if (timerstate == "TRUE") {
				ntstate = true;
			}
			else {
				ntstate = false;
			}

			homeDevices.push_back(new LightDevice(ndeviceName, nstate, ndeviceType, timernumint, ntstate, brightnessnumint));
		}


		else if (ndeviceType == "TempHumiditySensor") {
		
			getline(ss, ndeviceName, '|'); 
			string stateStr;
			getline(ss, stateStr, '|'); 
			bool nstate;

			string currenttemp;
			getline(ss, currenttemp, '|'); 
			int nctemp = stoi(currenttemp);
			string currenthumidity;
			getline(ss, currenthumidity, '|');
			int nchumidity = stoi(currenthumidity);
			string ntemp1;
			getline(ss, ntemp1, '|');
			int newtemp1 = stoi(ntemp1);
			string nhumidity1;
			getline(ss, nhumidity1, '|');
			int newhumidity1 = stoi(nhumidity1);
			string ntemp2;
			getline(ss, ntemp2, '|');
			int newtemp2 = stoi(ntemp2);
			string nhumidity2;
			getline(ss, nhumidity2, '|');
			int newhumidity2 = stoi(nhumidity2);
			


			if (stateStr == "TRUE") {
				nstate = true;
			}
			else {
				nstate = false;
			}

			map<int, int> nhistData;
			nhistData.insert({ newtemp1, newhumidity1 });//https://www.geeksforgeeks.org/map-insert-in-c-stl/
			nhistData.insert({ newtemp2, newhumidity2 });//data is inserted into a map for the historic data, each temperature is a key that matches to a humidty
			homeDevices.push_back(new TempHDevice(ndeviceName, nstate, ndeviceType, nctemp, nchumidity, nhistData));
		}

		else if (ndeviceType == "ThermoDevice") {
			
			getline(ss, ndeviceName, '|'); //https://www.geeksforgeeks.org/how-to-split-string-by-delimiter-in-cpp/
			//this helped me to learn how to use getline, to read up to the separator as my file is formatted by |
			string stateStr;
			getline(ss, stateStr, '|'); 
			bool nstate;
			string bstateStr;
			getline(ss, bstateStr, '|'); 
			bool nbstate;
		
			string ntime1;
			getline(ss, ntime1, '|');
			int newtime1 = stoi(ntime1);
			string ntime2;
			getline(ss, ntime2, '|');
			int newtime2 = stoi(ntime2);
			string ntime3;
			getline(ss, ntime3, '|');
			int newtime3 = stoi(ntime3);
			string ntime4;
			getline(ss, ntime4, '|');
			int newtime4 = stoi(ntime4);
		


			if (stateStr == "TRUE") {
				nstate = true;
			}
			else {
				nstate = false;
			}
			if (bstateStr == "TRUE") {
				nbstate = true;
			}
			else {
				nbstate = false;
			}
			map<int, int> nschedData;
			nschedData.insert({ newtime1, newtime2 });
			nschedData.insert({ newtime3, newtime4 });
			homeDevices.push_back(new ThermoDevice(ndeviceName, nstate, ndeviceType,  nschedData ,nbstate));
		}

		else if (ndeviceType == "RadiatorDevice") {

			getline(ss, ndeviceName, '|'); 
			string stateStr;
			getline(ss, stateStr, '|'); 
			bool nstate;
		

			string ntime1;
			getline(ss, ntime1, '|');
			int newtime1 = stoi(ntime1);
			string ntime2;
			getline(ss, ntime2, '|');
			int newtime2 = stoi(ntime2);
			string ntime3;
			getline(ss, ntime3, '|');
			int newtime3 = stoi(ntime3);
			string ntime4;
			getline(ss, ntime4, '|');
			int newtime4 = stoi(ntime4);
			

			string ntemp;
			getline(ss, ntemp, '|');
			double newtemp = stod(ntemp);

			if (stateStr == "TRUE") {
				nstate = true;
			}
			else {
				nstate = false;
			}
		
			map<int, int> nschedData;
			nschedData.insert({ newtime1, newtime2 });
			nschedData.insert({ newtime3, newtime4 });
			homeDevices.push_back(new RadiatorDevice(ndeviceName, nstate, ndeviceType, nschedData, newtemp));
			}

		else if (ndeviceType == "SocketDevice") {
		
			getline(ss, ndeviceName, '|'); 
			string stateStr;
			getline(ss, stateStr, '|');
			bool nstate;
			bool ntstate;
			string timerstate;
			getline(ss, timerstate, '|');
			string timernum;
			getline(ss, timernum, '|');
			int timernumint = stoi(timernum);
			string nusage;
			getline(ss, nusage, '|');
			int newusage = stoi(nusage);

			string ntime1;
			getline(ss, ntime1, '|');
			int newtime1 = stoi(ntime1);
			string ntime2;
			getline(ss, ntime2, '|');
			int newtime2 = stoi(ntime2);
			string ntime3;
			getline(ss, ntime3, '|');
			int newtime3 = stoi(ntime3);
			string ntime4;
			getline(ss, ntime4, '|');
			int newtime4 = stoi(ntime4);
	


			string nwatt1;
			getline(ss, nwatt1, '|');
			int newwatt1 = stoi(nwatt1);
			string nwatt2;
			getline(ss, nwatt2, '|');
			int  newwatt2 = stoi(nwatt2);
			string nwatt3;
			getline(ss, nwatt3, '|');
			int  newwatt3 = stoi(nwatt3);
			string nwatt4;
			getline(ss, nwatt4, '|');
			int  newwatt4 = stoi(nwatt4);
		
			if (stateStr == "TRUE") {
				nstate = true;
			}
			else {
				nstate = false;
			}
			if (timerstate == "TRUE") {
				ntstate = true;
			}
			else {
				ntstate = false;
			}

			map<int, int> nschedData;
			nschedData.insert({ newtime1, newtime2 });
			nschedData.insert({ newtime3, newtime4 });
			map<int, int> nhistData;
			nhistData.insert({ newwatt1,newwatt2 });
			nhistData.insert({ newwatt3, newwatt4 });
			SocketDevice* socketDevice = new SocketDevice(ndeviceName, nstate, ndeviceType, timernumint, ntstate, newusage, nschedData, nhistData);
			homeDevices.push_back((socketDevice));
			}
	}

	readFile.close();//close file
	return homeDevices;//returns vector with all objects loaded from the file
}

void updateFile(vector<SHDevice*> homeDevices){
	string textFile;
    ifstream readFile("alldevices.txt");//read from my devices 
    ofstream tempFile("tempdevices.txt");//create a temp file

    
    while (getline(readFile, textFile)) {
        stringstream ss(textFile);
      

        bool updated = false;

    
        for (auto it = homeDevices.begin(); it != homeDevices.end(); ++it) {//iterates through vector, using auto saves me from declaring the iterator saving time
			//https://stackoverflow.com/questions/12702561/iterate-through-a-c-vector-using-a-for-loop it is cleaner, NOTE CHANGE MAP ITERATORS AS WELL
			if (auto speakerDevice = dynamic_cast<SpeakerDevice*>((*it))) {//assesses which class the object comes from
				//again the auto keyword prevents uncessary errors, I don't have to write SpeakerDevice* i just write auto.
				tempFile << speakerDevice->getdeviceType() << "|"//writes the appropiate values back to the file in the same order as they are read
					<< speakerDevice->getName() << "|"
					<< (speakerDevice->getState() ? "TRUE" : "FALSE") << "|"//writes back in the format so it can be read back with no errors
					<< speakerDevice->getVolume() << endl;
				updated = true;
				
			}
			else if (auto thermoDevice = dynamic_cast<ThermoDevice*>((*it))) {
				map<int, int> schedData = thermoDevice->getschedData();
				
				tempFile << thermoDevice->getdeviceType() << "|"
					<< thermoDevice->getName() << "|"
					<< (thermoDevice->getState() ? "TRUE" : "FALSE") << "|"
					<< (thermoDevice->getboostState() ? "TRUE" : "FALSE") << "|";//uses get and set methods to get the attributes of the object

	
				map<int, int>::iterator itsched = schedData.begin();

				while (itsched != schedData.end()) {//iterates through the map, printing out the key and the value associated with it

					tempFile << itsched->first << "|" << itsched->second;


					if (next(itsched) != schedData.end()) {//this makes sure that the separator is not included at the end of the line, so null values aren't read from the file on the next opening
						tempFile << "|";
					}
					itsched++;
				}

				
				tempFile << endl;

				updated = true;
				
			}
			else if (auto lightDevice = dynamic_cast<LightDevice*>((*it))) {
				

				tempFile << lightDevice->getdeviceType() << "|"
					<< lightDevice->getName() << "|"
					<< (lightDevice->getState() ? "TRUE" : "FALSE") << "|"
					<< (lightDevice->getTimerState() ? "TRUE" : "FALSE") << "|" << lightDevice->getTimer() << "|" << lightDevice->getBrightness()  << endl;
				updated = true;
				
			
			}
			else if (auto temphDevice = dynamic_cast<TempHDevice*>((*it))) {
			
				map<int, int> histData = temphDevice->getHistData();

				tempFile << temphDevice->getdeviceType() << "|"
					<< temphDevice->getName() << "|"
					<< (temphDevice->getState() ? "TRUE" : "FALSE") << "|"// the set precision makes sure that the decimal places added during runtime are not omitted during the file update, i use setprecision followed by the number of decimal places (2)
					<< fixed << setprecision(2) <<(temphDevice->getCurrentTemp()) << "|"//https://stackoverflow.com/questions/35029233/set-precision-with-fstream-to-output-file-format-double#comment57784797_35029360
					<< (temphDevice->getCurrentHumidity()) << "|";



				map<int, int>::iterator ittemp = histData.begin();

				while (ittemp != histData.end()) {

					tempFile << ittemp->first << "|" << ittemp->second;


					if (next(ittemp) != histData.end()) {
						tempFile << "|";
					}
					ittemp++;
				}


				tempFile << endl;

				updated = true;
				
			
			
			
			
			}

			else if (auto socketDevice = dynamic_cast<SocketDevice*>((*it))) {
				
				map<int, int> schedData = (socketDevice)->getschedData();
				

				map<int, int> histData = socketDevice->gethistData();
				tempFile << socketDevice->getdeviceType() << "|"
					<< socketDevice->getName() << "|"
					<< (socketDevice->getState() ? "TRUE" : "FALSE") << "|"
					<< (socketDevice->getTimerState() ? "TRUE" : "FALSE") << "|"
					<< (socketDevice->getTimer()) << "|"
					<< (socketDevice->geteUse()) << "|";



				map<int, int>::iterator itsock = schedData.begin();

				while (itsock != schedData.end()) {

					tempFile << itsock->first << "|" << itsock->second << "|";

					itsock++;
				}

				map<int, int>::iterator itsock2 = histData.begin();

				while (itsock2 != histData.end()) {

					tempFile << itsock2->first << "|" << itsock2->second;


					if (next(itsock2) != histData.end()) {
						tempFile << "|";
					}
					itsock2++;
				}

				tempFile << endl;

				updated = true;
				
			}
            
			else if (auto radiatorDevice = dynamic_cast<RadiatorDevice*>((*it))) {
				map<int, int> schedData = radiatorDevice->getschedData();

				tempFile << radiatorDevice->getdeviceType() << "|"
					<< radiatorDevice->getName() << "|"
					<< (radiatorDevice->getState() ? "TRUE" : "FALSE") << "|";
					
				



				map<int, int>::iterator itrad = schedData.begin();//https://stackoverflow.com/questions/26281979/how-do-you-loop-through-a-stdmap
				//iterating through a map is very similar to vectors but i use first and second to access keys and values
				while (itrad != schedData.end()) {

					
					tempFile << itrad->first << "|" << itrad->second;

					
					if (next(itrad) != schedData.end()) {
						tempFile << "|";
					}
					itrad++;
				}


				
				tempFile << "|" << fixed << setprecision(2) << (radiatorDevice->getTemp());
				tempFile << endl;
				updated = true;
				




			}
		
        }
	
        if (!updated) {
            

            tempFile << textFile << endl;
        }
		else {
			break;
		}
    }

    readFile.close();
    tempFile.close();

  

	remove("alldevices.txt");
	rename("tempdevices.txt", "alldevices.txt"); //https://stackoverflow.com/questions/34507989/update-and-delete-data-from-file-in-c
	//these two lines, mean that the original file is deleted, my new file with all the updated object data, is renamed to the original file name making the read and write more efficient.
	//if i kept the same file, i would have to go through attribute by attribute checking for where values have changed
}


void lightDeviceMenu(vector<SHDevice*> homeDevices, LightDevice* lightDevice, bool fullfeature) {
	int i = 0, uchoice;
	string mm;
	
			
				if ( fullfeature == false) {//full fetaure controls whether i need to use the one click actions, or show all the actions available
					lightDevice->quickView();
					cout << "Press any key to go back to main menu\n";
					_getch();//https://coderslegacy.com/c/detect-key-presses-cpp
					//getch waits for a key input before moving on to the next line in code
					mainMenu(homeDevices);
					
					
					
					
			

					
				}
				else if (fullfeature == true) {// if user selects to see all attributes
					cout << "-------------------------------------------------------------\n";
					cout << "Press 1 to " << ((lightDevice)->getState() ? "turn off" : "turn on") << "\nPress 2 to change brightness" << "\nPress 3 to change device name" << "\nPress 4 to " << ((lightDevice)->getTimerState() ? "turn off" : " turn on")  << " sleep timer" << "\nPress 5 to change the Sleep Timer";
					cout << "\n-------------------------------------------------------------\n";
					//user can then select from an expanded range of options, instead of one click
					cin >> uchoice;
					if (uchoice == 1) {
						if ((lightDevice)->getState() == false) {

							(lightDevice)->setState(true);
							cout << "-------------------------------------------------------------\n";
							cout << "Light is now" << ((lightDevice)->getState() ? " on" : " off")<<"\n";//the get state determines the options available to the user
							cout << "-------------------------------------------------------------\n";

						}
						else {
							(lightDevice)->setState(false);
							cout << "-------------------------------------------------------------\n";
							cout << "Music is now" << ((lightDevice)->getState() ? " on" : " off")<<"\n";
							cout << "-------------------------------------------------------------\n";
						}

					}
					else if (uchoice == 2) {
						int brightness;
						cout << "-------------------------------------------------------------\n";
						cout << "Enter the new brightness for the device";
						cin >> brightness;
						lightDevice->setBrightness(brightness);
						cout << "Brightness is set to " << lightDevice->getBrightness() << "\n";
						cout << "-------------------------------------------------------------\n";

					}
					else if (uchoice == 3) {
						string name;
						cout << "-------------------------------------------------------------\n";
						cout << "Enter the new device name";
						cin >> name;
						lightDevice->setName(name);
						cout << "Name is set to " << lightDevice->getName() << "\n";
						cout << "-------------------------------------------------------------\n";

					}
					else if (uchoice == 4) {
						if (lightDevice->getTimerState() == false) {

							lightDevice->setTimerState(true);
							cout << "-------------------------------------------------------------\n";
							cout << "Sleep Timer is now" << (lightDevice->getTimerState() ? " off" : " off") << "\n";
							cout << "-------------------------------------------------------------\n";
						}
						else {
							lightDevice->setTimerState(false);
							cout << "-------------------------------------------------------------\n";
							cout << "Sleep Timer is now" << (lightDevice->getTimerState() ? " on" : " off") << "\n";
							cout << "-------------------------------------------------------------\n";
						}

					}
					else if (uchoice == 5) {
						int hours;
						"-------------------------------------------------------------\n";
						cout << "Enter the new length of sleep timer";
				
						cin >> hours;
						lightDevice->setTimer(hours);
						
						cout << "Sleep timer is set to " << lightDevice->getTimer() << " hours" << "\n";
						cout << "-------------------------------------------------------------\n";

					}
					else if (uchoice == 6) {
						
						mainMenu(homeDevices);

					}
				
				}



}

void speakerDeviceMenu(vector<SHDevice*> homeDevices, SpeakerDevice* device, bool fullfeature) {//the same code with the same premise then repeats for each device menu with different attributes accoridng to the class constructor
	int i = 0, uchoice;
	
	if (fullfeature == false) {
		device->quickView();
		cout << "\NPress any key to go back to main menu\n";
		_getch();
		mainMenu(homeDevices);

	}
	else if (fullfeature == true) {
		cout << "-------------------------------------------------------------\n";
		cout << "Press 1 to " << ((device)->getState() ? "pause" : "play") << "\nPress 2 to change volume" << "\nPress 3 to change device name\n" <<"Press 4 to go back to main menu";
		cout << "-------------------------------------------------------------\n";
		cin >> uchoice;
		if (uchoice == 1) {
			if ((device)->getState() == false) {

				(device)->setState(true);
				cout << "-------------------------------------------------------------\n";
				cout << "Music is now" << ((device)->getState() ? " playing" : " paused");
				cout << "-------------------------------------------------------------\n";
				
		

			}
			else {
				(device)->setState(false);
				cout << "-------------------------------------------------------------\n";
				cout << "Music is now" << ((device)->getState() ? " playing" : " paused") << "\n";
				cout << "-------------------------------------------------------------\n";
				
				
			}
			
		}
		else if (uchoice == 2) {
			int volume;
			cout << "-------------------------------------------------------------\n";
			cout << "Enter the new volume you would like to listen at";
			cin >> volume;
			device->setVolume(volume);
			cout << "Volume is set to " << device->getVolume();
			cout << "-------------------------------------------------------------\n";
			

		}
		else if (uchoice == 3) {
			string nname;
			cout << "-------------------------------------------------------------\n";
			cout << "Enter the new device name";
			cin >> nname;
			device->setName(nname);
			cout << "Name is set to " << device->getName();
			cout << "-------------------------------------------------------------\n";
		

		}
		else if (uchoice == 4) {
			mainMenu(homeDevices);

		}


	}
}

void tempHDeviceMenu(vector<SHDevice*> homeDevices, TempHDevice* tempHDevice, bool fullfeature) {
	int i = 0, uchoice;
	if (fullfeature == false) {
		tempHDevice->quickView();
		cout << "Press any key to go back to main menu\n";
		_getch();
		mainMenu(homeDevices);

		
		


	}
				if (fullfeature == true) {
					cout << "-------------------------------------------------------------\n";
					cout << "Press 1 to turn " << ((tempHDevice)->getState() ? "Off" : "On") << "\nPress 2 to view current temperature + humidity" << "\nPress 3 to view historic data\n" << "Press 4 to change device name\n" <<"Press 5 to return to the main menu";

					cin >> uchoice;
					if (uchoice == 1) {
						if ((tempHDevice)->getState() == false) {

							(tempHDevice)->setState(true);
							cout << "-------------------------------------------------------------\n";
							cout << "Temperature and Humidity Sensor is now" << ((tempHDevice)->getState() ? " On" : " Off") << "\n";
							cout << "-------------------------------------------------------------\n";
						}
						else {
							(tempHDevice)->setState(false);
							cout << "-------------------------------------------------------------\n";
							cout << "Temperature and Humidity Sensor is now" << ((tempHDevice)->getState() ? " On" : " Off") << "\n";
							cout << "-------------------------------------------------------------\n";
						}

					}
					else if (uchoice == 2) {

						cout << "-------------------------------------------------------------\n";
						cout << "The current temperature is " << tempHDevice->getCurrentTemp() << "\n";
						cout << "-------------------------------------------------------------\n";

						cout << "The current humidity is " << tempHDevice->getCurrentHumidity() << "\n";
						cout << "-------------------------------------------------------------\n";

					}
					else if (uchoice == 3) {
						tempHDevice->viewHistoric();

					}
					else if (uchoice == 4) {
						string name;
						cout << "-------------------------------------------------------------\n";
						cout << "Enter the new device name";
						cin >> name;
						tempHDevice->setName(name);
						cout << "Name is set to " << tempHDevice->getName();
						cout << "\n-------------------------------------------------------------\n";

					}

					else if (uchoice == 5) {
						
						mainMenu(homeDevices);

					}
				}
}


void thermoDeviceMenu(vector<SHDevice*> homeDevices, ThermoDevice* thermoDevice, bool fullfeature) {
	int i = 0, uchoice;
	if (fullfeature == false) {
		thermoDevice->quickView();
		cout << "Press any key to go back to main menu\n";
		_getch();
		mainMenu(homeDevices);
		

	}
	if (fullfeature == true) {
		cout << "-------------------------------------------------------------\n";
		cout << "Press 1 to turn " << ((thermoDevice)->getState() ? "Off" : "On") << "\nPress 2 to turn boost " << ((thermoDevice)->getboostState() ? "Off" : "On")<< "\nPress 3 to change schedules\n" << "Press 4 to change device name\n" << "Press 5 to go the main menu";

		cin >> uchoice;
		if (uchoice == 1) {
			if ((thermoDevice)->getState() == false) {

				(thermoDevice)->setState(true);
				cout << "-------------------------------------------------------------\n";
				cout << "Thermostat is now" << ((thermoDevice)->getState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}
			else {
				(thermoDevice)->setState(false);
				cout << "-------------------------------------------------------------\n";
				cout << "Thermostat is now" << ((thermoDevice)->getState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}

		}
		else if (uchoice == 2) {

			if ((thermoDevice)->getboostState() == false) {

				(thermoDevice)->setboostState(true);
				cout << "-------------------------------------------------------------\n";
				cout << "Heating boost is now" << ((thermoDevice)->getboostState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}
			else {
				(thermoDevice)->setboostState(false);
				cout << "-------------------------------------------------------------\n";
				cout << "Heating Boost is now" << ((thermoDevice)->getboostState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}

		}
		else if (uchoice == 3)
		{
			thermoDevice->viewSchedule();
			
			thermoDevice->setSchedule();
		
			cout << "-------------------------------------------------------------\n";
			
		}
		else if (uchoice == 4) {
			string name;
			cout << "-------------------------------------------------------------\n";
			cout << "Enter the new device name";
			cin >> name;
			thermoDevice->setName(name);
			cout << "Name is set to " << thermoDevice->getName();
			cout << "\n-------------------------------------------------------------\n";

		}

		else if (uchoice == 5) {
			mainMenu(homeDevices);

		}
	}
}




void radiatorDeviceMenu(vector<SHDevice*> homeDevices, RadiatorDevice* radiatorDevice, bool fullfeature) {
	int i = 0, uchoice;
	if (fullfeature == false) {
		radiatorDevice->quickView();
		cout << "Press any key to go back to main menu\n";
		_getch();
		mainMenu(homeDevices);


	}
	if (fullfeature == true) {
		cout << "-------------------------------------------------------------\n";
		cout << "Press 1 to turn " << ((radiatorDevice)->getState() ? "Off" : "On") << "\nPress 2 to change temperature " << "\nPress 3 to change schedules\n" << "Press 4 to change device name\n" <<"Press 5 to return to the main menu";

		cin >> uchoice;
		if (uchoice == 1) {
			if ((radiatorDevice)->getState() == false) {

				(radiatorDevice)->setState(true);
				cout << "-------------------------------------------------------------\n";
				cout << "Radiator is now" << ((radiatorDevice)->getState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}
			else {
				(radiatorDevice)->setState(false);
				cout << "-------------------------------------------------------------\n";
				cout << "Radiator is now" << ((radiatorDevice)->getState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}

		}
		else if (uchoice == 2) {
			double temp;
			cout << "What temperature would you like it to reach?";
			cin >> temp;
			(radiatorDevice)->setTemp(temp);
			cout << "-------------------------------------------------------------\n";
			cout << "Temperature is now heating to  " << ((radiatorDevice)->getTemp()) << "\n";
			cout << "-------------------------------------------------------------\n";
			
			
		}
		else if (uchoice == 3)
		{
			radiatorDevice->viewSchedule();
			
			radiatorDevice->setSchedule();

			cout << "-------------------------------------------------------------\n";
			
		}
		else if (uchoice == 4) {
			string name;
			cout << "-------------------------------------------------------------\n";
			cout << "Enter the new device name";
			cin >> name;
			radiatorDevice->setName(name);
			cout << "Name is set to " << radiatorDevice->getName();
			cout << "\n-------------------------------------------------------------\n";

		}

		else if (uchoice == 5) {
			mainMenu(homeDevices);

		}

	}
}



void socketDeviceMenu(vector<SHDevice*> homeDevices, SocketDevice* socketDevice, bool fullfeature) {
	int i = 0, uchoice;
	if (fullfeature == false) {

		socketDevice->quickView();
		cout << "Press any key to go back to main menu\n";
		_getch();
		mainMenu(homeDevices);



	}
	if (fullfeature == true) {
		cout << "-------------------------------------------------------------\n";
		cout << "Press 1 to turn " << ((socketDevice)->getState() ? "Off" : "On") << "\nPress 2 to turn timer " << ((socketDevice)->getTimerState() ? "Off" : "On") << "\nPress 3 to change schedules"  << "\nPress 4 to view historic data" << "\nPress 5 to change device name" <<"\nPress 6 to return to Main Menu\n";

		cin >> uchoice;
		if (uchoice == 1) {
			if ((socketDevice)->getState() == false) {

				(socketDevice)->setState(true);
				cout << "-------------------------------------------------------------\n";
				cout << "Socket is now" << ((socketDevice)->getState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}
			else {
				(socketDevice)->setState(false);
				cout << "-------------------------------------------------------------\n";
				cout << "Socket is now" << ((socketDevice)->getState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}

		}
		else if (uchoice == 2) {
			if ((socketDevice)->getTimerState() == false) {

				(socketDevice)->setTimerState(true);
				cout << "-------------------------------------------------------------\n";
				cout << "Socket is now" << ((socketDevice)->getTimerState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}
			else {
				(socketDevice)->setTimerState(false);
				cout << "-------------------------------------------------------------\n";
				cout << "Socket is now" << ((socketDevice)->getTimerState() ? " On" : " Off") << "\n";
				cout << "-------------------------------------------------------------\n";
			}
		}
		else if (uchoice == 3)
		{
			socketDevice->viewSchedule();
			socketDevice->setSchedule();
			
		}

		else if (uchoice == 4)
		{
			socketDevice->viewHistoric();
		
		}

		else if (uchoice == 5) {
			string name;
			cout << "-------------------------------------------------------------\n";
			cout << "Enter the new device name";
			cin >> name;
			socketDevice->setName(name);
			cout << "Name is set to " << socketDevice->getName();
			cout << "\n-------------------------------------------------------------\n";

		}

		else if (uchoice == 6) {
			mainMenu(homeDevices);
		}

		

	}
}

int getRandomSched() {//when a user adds a device, a random number between 0 and 2400 is generated. this is generated and then formatted into 24 hour timne as demonstrated below
	uniform_int_distribution<> distrib(0, 2400);
	
	int unformatted = static_cast<double>(distrib(gen));//eg if equals 1475
	if (unformatted % 100 > 60) {
		double hoursformat = unformatted / 100; //14 as it only gives full part so 14 hours
		double minuteformat = unformatted % 100; //1475 mod 100 = 75
		double formatmins = (minuteformat / 100) * 60; // 75/100 = 0.75 * 60 = 45 so 45 mins
		double formathours = hoursformat * 100; //14 becomes 1400;
		int formatted = formathours + formatmins;
		return formatted;
	}
	
	else {

		return unformatted;
	}

	
}

map<int, int> getRandomSchedData() {//this then generates the map from the random values in the previous section
	map<int, int> schedData;

	int time1 = getRandomSched();
	int time2 = getRandomSched();
	while (time1 > time2) {//this makes sure the earliest time is first, it would be confusing to have a schedule of 1700 to 0800 in one day
		time2 = getRandomSched();
	}
	int time3 = getRandomSched();
	int time4 = getRandomSched();
	while (time3 > time4) {
		time4 = getRandomSched();
	}

	schedData.insert({ time1,time2 });
	schedData.insert({ time3,time4 });

	return schedData;
}

map<int, int> getRandomHistData() {//the random humidity and temperature is more simple, based on the same distibution but values are directly generated
	map<int, int> histData;

	uniform_int_distribution<> distrib(0, 100);
	histData.insert({ distrib(gen), distrib(gen) });//https://www.geeksforgeeks.org/how-to-generate-random-number-in-range-in-cpp/
	histData.insert({ distrib(gen), distrib(gen) });
	return histData;
}



string mainMenuValidation(string input, vector<SHDevice*> homeDevices) {
	bool validinput = false;
	vector<SHDevice*>::iterator it(homeDevices.begin());
	while (validinput != true) {
		try {
			if (stoi(input) <= homeDevices.size() + 3 && stoi(input) > 0) {//this checks the main menu input is in range, it does not exceed the amount of numbers available to choose from
				validinput = true;
				return input;
			}
		}

		catch (const std::invalid_argument& e) {//https://stackoverflow.com/questions/59457656/exception-handling-with-stoi-function
			//if a user enters a name of the device, to access full features, the stoi arguement presents an error, if i have a catch option that catches this error, the device name can be checked after
			
		}


		
		//https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
		//this section compares the name of the device the user has entered, if it matches first time it is accepted
		//if it doesn't compare exatly, the lower case version is checked, and that is accepted if so
		for (it = homeDevices.begin(); it != homeDevices.end(); ++it) {
			string name = (*it)->getName();
			transform(name.begin(), name.end(), name.begin(), ::tolower);//this goes through the string making each character lower case, using the transform function
			
			if (input == (*it)->getName()) {
				validinput = true;//match first time
				return input;


				
				//checks if the name entered is in the homeDevices vector 
			}

			transform(input.begin(), input.end(), input.begin(), ::tolower);
			if (input == name) {
				validinput = true;//matches on lower case
				string newinput = (*it)->getName();
				return newinput;
			}
			


		}

		if (input == "E" || input == "A" || input == "e" || input == "a" || input == "D" || input == "d") {

			validinput = true;
			return input;
		}//allows for lower case


		else {
			cout << "Out of range/Does not exist";
			cout << "\nPlease enter your selection again...\n";
			cin >> input;//repeats asking for a valid input till it matches a condition


		}

		
		
	}
}

string removeSpaces(string input,vector<SHDevice*> homeDevices) {//when a user adds a device, they may want to enter a name with spaces
	string newstring;//this is not the naming convention i use in my file, this removes the spaces and replaces them with an underscore
	bool unique = false;
	vector<SHDevice*>::iterator it(homeDevices.begin());
	while (unique == false) {
		for (int i = 0; i < input.size(); i++) {
			if (input[i] != ' ') {
				newstring += input[i];
			}
			else if (input[i] = ' ') {
				newstring += "_";
			}
		}

		while (it != homeDevices.end()) {
			if (newstring == (*it)->getName()) {
				cout << "Name already exists, enter again";
			
				getline(cin, input);
				newstring = "";
				break;
			}
			else {
				 unique = true;
				 break;
			}

		}
	}
	
	
	return newstring;
}
	

string removeDevice(string input, vector<SHDevice*> homeDevices) {//when a user adds a device, they may want to enter a name with spaces or with the incorrect cases
	string newstring;//this is not the naming convention i use in my file, this removes the spaces and replaces them with an underscore then checks the irst and letter after the underscore are upper case
	bool unique = false;
	vector<SHDevice*>::iterator it(homeDevices.begin());

		for (int i = 0; i < input.size(); i++) {//traverses through input
			if (input[i] != ' ') {//if character != space
				
				if (i == 0 && islower(input[i])) {//checks if the first character is lowercase
					input[i] = toupper(input[i]);//makes it uppercase
					newstring += input[i];//adds to cleansed string
				}
				else if (!newstring.empty() && newstring[i-1] == '_') {//https://www.geeksforgeeks.org/std-string-empty-in-cpp/
					//
					input[i] = toupper(input[i]);//if after hypen,change to upper case
					newstring += input[i];//add
				}
				else {
					newstring += input[i];//if it doesnt match add it as it is
				}
			}
			else if (input[i] == ' ') {//if spaces, change to hyphen
				newstring += "_";

			}
		
			
			
			
		}

		
	


	return newstring;
}





void mainMenu(vector<SHDevice*> homeDevices) {//this menu controls my whole program
	
	int i = 1;
	bool fullfeature;
	string input;
	vector<SHDevice*>::iterator it(homeDevices.begin());//iterates through home devices, and prints out a list of them promting the user to select one click or full features

	while (it != homeDevices.end()) {
		cout << "\nSelect "
			<< (*it)->getName() << " : Perform that device's one - click action (type name) \n"
			<< i << " : " << (*it)->getName() << " Select device number to interact with it's full feature set\n";

		cout << "------------------------------------------------";
		it++;
		i++;
		if (it == homeDevices.end()) {

			cout << "\n" << i << " : List devices\n"
				<< i + 1 << " : Sort by name\n"
				<< i + 2 << " : Sort by device type(by name as secondary order)\n"
				<< "A : Add device\n"
				<<"D : Delete device\n"
				<< "E : Exit\n";
			cout << "------------------------------------------------\n";
			//the numbers for the menu are based off the size of the home devices 
			cin >> input;
			input = mainMenuValidation(input, homeDevices);//input is validated
			int i3 = 1;
			//https://www.gormanalysis.com/blog/sorting-a-vector-in-cpp/
			//i then present options to either interact with a device, list, sort by name, sort by type then name as secondary order
			if (input == "E" || input == "e") {
				updateFile(homeDevices);//if the user wants to exit all vectors are loaded in the file 
				
				exit(0);
			}
			if (input == "D" || input == "d") {
				
				string namedelete;
				for (it = homeDevices.begin(); it != homeDevices.end(); ++it) {
					cout << (*it)->getName() << "\n";
				}

				cout << "Type the name of the device to delete: ";

				cin.ignore();
				getline(cin, namedelete);

				for (it = homeDevices.begin(); it != homeDevices.end(); ) {
			
					if (removeDevice(namedelete, homeDevices) == (*it)->getName()) {
						it = homeDevices.erase(it);//https://stackoverflow.com/questions/11773787/deleting-an-object-in-a-vector erases object using the function .erase()
						cout << "Device erased\n";
						cout << "Press any key to go back to main menu\n";
						_getch();
						mainMenu(homeDevices);
						break;
						
					}
					else {
						++it;
					}
				}
			}
			if (input == "A" || input == "a") {
				int intinput;//if a is selected then the user starts the process to add a device

				cout << "Type number of the device category you would like to add!\n" << "1.SpeakerDevice\n2.TempHDevice (temperature and humidity sensor)\n3.RadiatorDevice\n4.SocketDevice\n5.ThermoDevice (thermostat)\n6.LightDevice\n";
				cin >> intinput;
				cin.ignore();//this prevents the option to input being skipped with getline in place.
				string name;
				cout << "Enter the device name: "; //https://stackoverflow.com/questions/40984752/c-input-string-with-spaces
				getline(cin, name); //get line takes the input with spaces to be cleansed by my validation function
				name = removeSpaces(name,homeDevices);


				switch (intinput) {
				case 1:

					homeDevices.push_back(new SpeakerDevice(name, false, "Speaker", 0));
					break;


				case 2:


					homeDevices.push_back(new TempHDevice(name, false, "TempHumiditySensor", 0.0, 0.0, getRandomHistData()));

					break;

				case 3:


					homeDevices.push_back(new RadiatorDevice(name, false, "RadiatorDevice", getRandomSchedData(), 0.0));

					break;

				case 4:


					homeDevices.push_back(new SocketDevice(name, false, "SocketDevice", 0, false, 0, getRandomSchedData(), getRandomHistData()));

					break;

				case 5:


					homeDevices.push_back(new ThermoDevice(name, false, "ThermoDevice", getRandomSchedData(), false));

					break;


				case 6:


					homeDevices.push_back(new LightDevice(name, false, "LightDevice", 0, false, 0));

					break;
				}
				//when the device type is checked, it is pushed into the vector with default values, so it immediately works in the system. the values have to be taailored to the individuual classes as they
				//may share attributes but they can also have new one


				cout << "Device added successfully";
				mainMenu(homeDevices);
				break;//user is promted to go back to the main menu and completed device addition is printed



			}
			it = (homeDevices.begin());
			while (it != homeDevices.end()) {
				if (input == to_string(i3)) {
					fullfeature = true;//when the user selects by name the full features of device can be interacted with
					SHDevice* device;
					//the class of the object is checked, then the user is directed to the appropiate device menu, to select what they would like to do with the object
					if (auto speakerDevice = dynamic_cast<SpeakerDevice*>((*it))) {
						speakerDeviceMenu(homeDevices, speakerDevice, fullfeature);
						while (nav(homeDevices) == true) {
							speakerDeviceMenu(homeDevices, speakerDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
					if (auto tempHDevice = dynamic_cast<TempHDevice*>((*it))) {
						tempHDeviceMenu(homeDevices, tempHDevice, fullfeature);
						while (nav(homeDevices) == true) {
							tempHDeviceMenu(homeDevices, tempHDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
					//if (auto tDevice = dynamic_cast<TDevice*>((*it))) {
					if (auto lightDevice = dynamic_cast<LightDevice*>(/*tDevice*/*it)) {
						lightDeviceMenu(homeDevices, lightDevice, fullfeature);
						while (nav(homeDevices) == true) {
							lightDeviceMenu(homeDevices, lightDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
					//}

					//if (auto schedDevice = dynamic_cast<SchedDevice*>((*it))) {
					if (auto thermoDevice = dynamic_cast<ThermoDevice*>(/*tDevice*/*it)) {
						thermoDeviceMenu(homeDevices, thermoDevice, fullfeature);
						while (nav(homeDevices) == true) {
							thermoDeviceMenu(homeDevices, thermoDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
					//}

					//if (auto schedDevice = dynamic_cast<SchedDevice*>((*it))) {
					if (auto radiatorDevice = dynamic_cast<RadiatorDevice*>(/*tDevice*/*it)) {
						radiatorDeviceMenu(homeDevices, radiatorDevice, fullfeature);
						while (nav(homeDevices) == true) {
							radiatorDeviceMenu(homeDevices, radiatorDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
					//}
					if (auto socketDevice = dynamic_cast<SocketDevice*>(/*tDevice*/*it)) {
						socketDeviceMenu(homeDevices, socketDevice, fullfeature);
						while (nav(homeDevices) == true) {
							socketDeviceMenu(homeDevices, socketDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
				}




				//when the user selects a device by number it is only the one click actions that can be interacted with
				if ((*it)->getName() == input) {
					SHDevice* device;
					fullfeature = false;
					if (auto speakerDevice = dynamic_cast<SpeakerDevice*>((*it))) {
						speakerDeviceMenu(homeDevices, speakerDevice, fullfeature);
						while (nav2(homeDevices) == true) {
							speakerDeviceMenu(homeDevices, speakerDevice, fullfeature);
						}

						mainMenu(homeDevices);


					}
					if (auto tempHDevice = dynamic_cast<TempHDevice*>((*it))) {
						tempHDeviceMenu(homeDevices, tempHDevice, fullfeature);
						while (nav2(homeDevices) == true) {
							tempHDeviceMenu(homeDevices, tempHDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
					//if (auto tDevice = dynamic_cast<TDevice*>((*it))) { THIS WAS THE PROCESS I WAS USING TILL I IMPLEMETED THE VIRTUAL INHERITANCE STRUCTURE
					if (auto lightDevice = dynamic_cast<LightDevice*>(/*tDevice*/*it)) {
						lightDeviceMenu(homeDevices, lightDevice, fullfeature);
						while (nav2(homeDevices) == true) {
							lightDeviceMenu(homeDevices, lightDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}


					//}

					//if (auto schedDevice = dynamic_cast<SchedDevice*>((*it))) {
					if (auto thermoDevice = dynamic_cast<ThermoDevice*>(/*tDevice*/*it)) {
						thermoDeviceMenu(homeDevices, thermoDevice, fullfeature);
						while (nav(homeDevices) == true) {
							thermoDeviceMenu(homeDevices, thermoDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
					//}

					//if (auto schedDevice = dynamic_cast<SchedDevice*>((*it))) {
					if (auto radiatorDevice = dynamic_cast<RadiatorDevice*>(/*tDevice*/*it)) {
						radiatorDeviceMenu(homeDevices, radiatorDevice, fullfeature);
						while (nav(homeDevices) == true) {
							radiatorDeviceMenu(homeDevices, radiatorDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
					//}
					if (auto socketDevice = dynamic_cast<SocketDevice*>(/*tDevice*/*it)) {
						socketDeviceMenu(homeDevices, socketDevice, fullfeature);
						while (nav(homeDevices) == true) {
							socketDeviceMenu(homeDevices, socketDevice, fullfeature);
						}

						mainMenu(homeDevices);

					}
				}
				i3++;
				it++;


				if (input == to_string(i)) {
					cout << "------------------------------------------------\n";
					for (it = homeDevices.begin(); it != homeDevices.end(); ++it) {
						
						cout << (*it)->getName() << "\n";
						(*it)->quickView();
						cout << "\n\n";

						if (next(it) != homeDevices.end()) {
							cout << "Next item in list: ";
						}
					}

					if (nav3(homeDevices) == true) {
						mainMenu(homeDevices);
						//checks if the user wants to return to the main menu
					}
				}
				i = i + 1;
				if (input == to_string(i)) {//sorts the devices in a list by name
					sort(homeDevices.begin(), homeDevices.end(),
						[](SHDevice* a, SHDevice* b) { return a->getName() < b->getName(); });


					for (SHDevice* x : homeDevices) std::cout << x->getName() << "\n";
					if (nav3(homeDevices) == true) {
						mainMenu(homeDevices);
					}
				}
				i = i + 1;
				if (input == to_string(i)) {
					//https://dev.to/rajat_naegi/understanding-std-sort-especially-the-third-parameter-14k4
					sort(homeDevices.begin(), homeDevices.end(),
						[](SHDevice* a, SHDevice* b) {//sort function through the vector
							if (a->getdeviceType() == b->getdeviceType()) {//if the device types are the same
								return a->getName() < b->getName();//then sort by name alphabetically


							}
							return a->getdeviceType() < b->getdeviceType();
							//sorts by device type and name by secondary order

						});
					for (SHDevice* device : homeDevices) {
						std::cout << device->getName() << "\n";
					}
					if (nav3(homeDevices) == true) {
						mainMenu(homeDevices);
					}
				}

				
			}
		}
	}

}


void SHMenu(vector<SHDevice*> homeDevices) {

		mainMenu(homeDevices);//mainMenu fucntion is called
}


int main() {
	system("Color 0B");//https://iq.opengenus.org/print-text-in-color-in-c/
	system("color 00");//colour is changed for the text
	vector<SHDevice*> homeDevices;
	homeDevices = readFile(homeDevices);//vector is created and passed to the function that reads from the text file on program start
	SHMenu(homeDevices);
	
}
	



	
	
