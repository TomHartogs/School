#include "Sedan.h"

// TODO: implement your class methods here
double pricePerKm = 0.29;

Sedan::Sedan(string manufacturer, string model, int buildYear,
                     string licencePlate, bool hasTowBar)
    : Car(manufacturer, model, buildYear, licencePlate, pricePerKm)
    ,hasTowBar(hasTowBar)
    ,lastCleanedAtKm(0)
{}

bool Sedan::HasTowBar() const {return hasTowBar;}

bool NeedsCleaning()
{
	bool needsCleaning = ((GetKilometers() - lastCleanedAtKm) >= 1000);
	return true;
}

void Clean()
{
	lastCleanedAtKm = GetKilometers();
}
