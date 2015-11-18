#ifndef __LIMOUSINE_H
#define __LIMOUSINE_H

#include "Car.h"

// TODO: your class definition goes here
class Limousine: public Car
{
	public:
	bool HasMiniBar() const;
	
	Limousine(string manufacturer, string model, int buildYear,
			  string licensePlate ,bool hasMiniBar);
	
	void Clean();
	
	private:
	static double const pricePerKm;
	bool hasMiniBar;
};

#endif
