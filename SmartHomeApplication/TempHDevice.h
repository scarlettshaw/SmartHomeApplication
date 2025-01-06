#pragma once
#include "SHDevice.h"
#include <map>
class TempHDevice : public SHDevice
{
public:
	//getter and setter for attributes with quick view function and constructor based on additional attributes needed from base class
	TempHDevice(string deviceName, bool state, string deviceType, double currenttemp, double currenthumidity, map<int, int> histData);
	void setHistData(double temp, double humidity);
	map<int,int> getHistData() const { return histData; }
	void viewHistoric();
	double setCurrentTemp(const double& ctemp) { currenttemp = ctemp; }
	double getCurrentTemp() const { return currenttemp; }
	double setCurrentHumidity(const double& chumidity) { currenthumidity = chumidity; }
	double getCurrentHumidity() const { return currenthumidity; }
	double setTemp(const double& ntemp) { temp = ntemp; }
	double getTemp() const { return temp; }
	double setHumidity(const double& nhumidity) { humidity = nhumidity; }
	double getHumidity() const { return humidity; }
	
	void quickView();
private:
	double currenttemp;
	double currenthumidity;
	double temp;
	double humidity; 
	//https://www.geeksforgeeks.org/how-to-create-a-dictionary-in-cpp/
	 map<int, int> histData;
};

