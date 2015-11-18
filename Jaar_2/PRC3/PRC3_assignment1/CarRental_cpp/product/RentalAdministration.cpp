#include "RentalAdministration.h" 
#include <stdexcept>

vector<Car*> cars;

RentalAdministration::RentalAdministration()
{}

vector<Car*> GetCars()
{
	return cars;
}

bool Add(Car* car)
{
	if(!car)
	{
		throw invalid_argument("car pointer == NULL");
	}
	if(!FindCar(car->GetLicensePlate()))
	{
		return false;
	}
	cars.push_back(car);
	return true;
}

bool RentCar(string licensePlate)
{
	Car* car = findCarWithException(licensePlate);
	return car->Rent();
}

double ReturnCar(string licensePlate, int kilometers)
{
	Car* car = FindCarWithException(licensePlate);
	
	if (car->IsAvailable())
	{
		throw logic_error ("car was not rented");
	}
	return car->Return(kilometers);
}

void CleanCar(string licensePlate)
{
	Car* car = FindCarWithException(licensePlate);
	if(car)
	{
		car->Clean();	
	}	
}

Car* FindCar(string licensePlate)
{
	for(int i = 0; i < (int)cars.size(); i++)
	{
		if (cars[i]->GetLicensePlate() == licensePlate)
		{
			return cars[i];
		}
	}
	return NULL;
}

Car* FindCarWithException(string licensePlate)
{
	Car* car = FindCar(licensePlate);
	if (!car)
	{
		throw invalid_argument("no car with this licenceplate in administration");
	}
	return car;
}
