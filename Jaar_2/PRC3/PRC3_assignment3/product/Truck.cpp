#include "Truck.h"
#include <stdexcept>

Truck::Truck(const string& model, const string& material, int diameter, int nrWheels, int power)
	: Car(model, material, diameter, nrWheels)
	, power(&power)
{
	if(power < 0)
		throw std::invalid_argument("Power needs to be more than 0");
}

Truck::~Truck()
{
	//??
	delete power;
}

int Truck::getPower() { return *power; }

Truck::Truck(const Truck& myTruck)
	: Car(myTruck)
{
	power = new int(*myTruck.power);
}

Truck& Truck::operator=(const Truck& myTruck)
{
	Car::operator=(myTruck);
	if (&myTruck == this) 
		return *this;
		
	//??
    delete power;
    power = new int(*myTruck.power);
    return *this;
}
