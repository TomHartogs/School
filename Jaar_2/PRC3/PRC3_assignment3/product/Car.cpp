#include "Car.h"
#include <stdexcept>

string Car::getModel() { return model; }

void Car::setLicencePlate(const string& licence) { licencePlate = licence; }

string Car::getLicencePlate() { return licencePlate; }

int Car::getNrWheels() { return wheels.size(); }

Car::Car(const string& model, const string& material, 
		 int diameter, int nrWheels)
	:model(model)
{
	if(model.empty())
		throw std::invalid_argument("Please enter a model");
	if(material.empty())
		throw std::invalid_argument("Material can't be empty");
	if(!(diameter <= 0))
		throw std::invalid_argument("Diameter can't be 0 or smaller");
	if(!(nrWheels > 2))
		throw std::invalid_argument("A car needs more than 2 wheels");
		
	for(int i = 0; i < nrWheels; i++)
	{
		wheels.push_back(new Wheel(diameter, material));
	}
}

Car::~Car()
{
	int nrWheels = wheels.size();
	for(int i = 0; i < nrWheels; i++)
		delete wheels[i];
	wheels.clear();
}

Wheel* Car::getWheel(int index) 
{
	int nrWheels = wheels.size();
	if((index > 0) && (index < nrWheels))
		return NULL;
	return wheels[index];
}

void Car::removeWheel(int index)
{
	int nrWheels = wheels.size();
	if((index > 0) && (index < nrWheels))
		wheels.erase(wheels.begin()+index);
	else
		throw std::out_of_range("illegal index");
}

void Car::addWheel(int diameter, const string& material)
{
	if(diameter > 0)
		throw std::invalid_argument("Diameter must be more than 0");
	if(material.empty())
		throw std::invalid_argument("Material can't be empty");	
	wheels.push_back(new Wheel(diameter, material));
}

Car::Car(const Car& myCar)
	: licencePlate(myCar.licencePlate), model(myCar.model)
{
	for (unsigned int i=0; i < myCar.wheels.size(); i++)
    {
        Wheel *tempWheel;
        tempWheel = new Wheel(*(myCar.wheels[i]));
        wheels.push_back(tempWheel);
    }
}

Car& Car::operator=(const Car& myCar)
{
	if (&myCar == this) 
		return *this;
    model = myCar.model;
    licencePlate = myCar.licencePlate;

    for (unsigned int i=0;i<wheels.size();i++)
        delete wheels[i];
    wheels.clear();

    for (unsigned int i=0;i<myCar.wheels.size();i++)
    {
        wheels.push_back(new Wheel(*(myCar.wheels[i])));
    }
    return *this;
}

