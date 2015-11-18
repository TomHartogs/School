#ifndef __RENTALADMINISTRATION_H
#define __RENTALADMINISTRATION_H

#include <string>
#include <vector>
#include "Car.h"
using namespace std;

class RentalAdministration
{
	public:
	RentalAdministration();

	bool Add(Car* car);
	bool RentCar(string licensePlate);
	double ReturnCar(string licensePlate, int kilometers);
	void CleanCar(string licensePlate);
	vector<Car*> GetCars();

	private:
	vector<Car*> cars;
	Car* FindCar(string licensePlate);
	Car* FindCarWithException(string licensePlate);
};

#endif
