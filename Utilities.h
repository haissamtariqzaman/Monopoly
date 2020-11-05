#pragma once

class Utilities
{
public:
	Utilities(bool=0,bool=0,bool=0);
	void setWifi(bool);
	void setGas(bool);
	void setElectricity(bool);
	bool getWifi();
	bool getGas();
	bool getElectricity();
private:
	bool wifi;
	bool gas;
	bool electricity;
};