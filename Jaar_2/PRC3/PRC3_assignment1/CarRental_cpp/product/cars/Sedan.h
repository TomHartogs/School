#ifndef __SEDAN_H
#define __SEDAN_H

#include "Car.h"

// TODO: your class definition goes here
class Sedan: public Car
{
	public:
	bool HasTowBar() const;
	bool NeedsCleaning();
	
	Sedan(string manufacturer, string model, int buildYear,
			  string licensePlate, bool hasMiniBar);
	
	void Clean();
	
	private:
	bool hasTowBar;
	int lastCleanedAtKm;
	static const double pricePerKm;
};

#endif
