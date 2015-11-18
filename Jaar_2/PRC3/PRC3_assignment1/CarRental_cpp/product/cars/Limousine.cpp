#include "Limousine.h"

// TODO: implement your class methods here
double pricePerKm = 2.5;

Limousine::Limousine(string manufacturer, string model, int buildYear,
                     string licencePlate, bool hasMinibar)
    : Car(manufacturer, model, buildYear, licencePlate, pricePerKm)
    ,hasMiniBar(hasMiniBar)
{}

void Clean()
{
	needsCleaning = false;
}

bool Limousine::HasMiniBar() const {return hasMiniBar;}

