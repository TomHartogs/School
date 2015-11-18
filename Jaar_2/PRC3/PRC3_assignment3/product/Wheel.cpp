#include <stdexcept>
#include "Wheel.h"

string Wheel::getMaterial() { return material; }

void Wheel::setMaterial(const string& material) { this->material = material; }

int Wheel::getDiameter() { return diameter; }

Wheel::Wheel(int diameter, const string& material)
		:diameter(diameter), material(material)
{
	if(diameter <= 0)
		throw std::invalid_argument("Diameter can't be 0 or smaller");
	if(material.empty())
		throw std::invalid_argument("Please enter material");
}

