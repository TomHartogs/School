#ifndef __CAR_H
#define __CAR_H

#include <string>
using namespace std;

// TODO: your class definition goes here
class Car
{
	public:
	string GetManufacturer() const;
	string GetModel() const;
	string GetLicensePlate() const;
	int GetBuildYear() const;
	int GetKilometers() const;
	bool IsAvailable() const;
	bool NeedsCleaning() const;
	
	Car(string manufacturer, string model, int buildYear,
		string licensePlate, double pricePerKm);
	
	bool Rent();
	virtual double Return(int kilometers);
	virtual void Clean() = 0;
	string ToString() const;
	
	private:
	string manufacturer;
	string model;
	int buildYear;
	string licensePlate;
	int kilometers;
	bool needsCleaning; 
	bool isAvailable;
	double pricePerKm;
};

#endif
