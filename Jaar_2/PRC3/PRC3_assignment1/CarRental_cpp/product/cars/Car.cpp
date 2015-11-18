
using namespace std;

#include "Car.h"

// TODO: implement your class methods here

Car::Car(string manufacturer, string model, int buildYear,
		 string licensePlate, double pricePerKm)
	: manufacturer(manufacturer)
	, model(model)
	, buildYear(buildYear)
	, licensePlate(licensePlate)
	, kilometers(0)
	, needsCleaning(false)
	, isAvailable(true)
	, pricePerKm(pricePerKm)
{}

string Car::GetManufacturer() const {return manufacturer;}
string Car::GetModel() const {return model;}
int Car::GetBuildYear() const {return buildYear;}
string Car::GetLicensePlate() const {return licensePlate;}
bool Car::NeedsCleaning() const {return needsCleaning;}
int Car::GetKilometers() const {return kilometers;}
bool Car::IsAvailable() const {return isAvailable;}

bool Car::Rent()
{
	if (!IsAvailable())
	{
		return false;
	}
	
	return true;
}
double Car::Return(int newKilometers)
{
	if(IsAvailable())
	{
		std::except::throw logic_error ("car was not rented");
	}
	if(kilometers < GetKilometers())
	{
		throw invalid_argument("car is returned with less kilometers than it had");
	}
	double cost = pricePerKm * (kilometers - GetKilometers());
	kilometers = newKilometers;
	needsCleaning = true;
	isAvailable = true;
	return cost;
}

void Car::Clean()
{
	needsCleaning = false;
}

string Car::ToString() const 
{
	return manufacturer +
	   " - " + model +
	   ", " + licensePlate;
}

