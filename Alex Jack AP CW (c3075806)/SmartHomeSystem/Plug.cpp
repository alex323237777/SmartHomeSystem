#include "Plug.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Plug::Plug(const std::string& plugName, bool isPlugOn, double Lusage, double Husage)
	: Device(plugName), isOn(isPlugOn), live(Lusage), historic(Husage) {}

void Plug::quickView() const
{
	std::cout << *this;
}

void Plug::displayDetails() const
{
	std::cout << *this;
}

std::string Plug::toFileString() const
{
	std::ostringstream ss;
	ss << name << "," << isOn << "," << live << "," << historic;
	return ss.str();
}

Plug Plug::fromFileString(const std::string& data)
{
	std::istringstream ss(data);
	std::string name;
	bool isOn;
	double live, historic;

	std::getline(ss, name, ',');
	ss >> isOn;
	ss.ignore();
	ss >> live;
	ss.ignore();
	ss >> historic;

	return Plug(name, isOn, live, historic);
}

std::ostream& operator<<(std::ostream& os, const Plug& plug)
{
	os << "\nPlug: " << plug.name << "\nStatus: " << (plug.isOn ? "On" : "Off") << "\nLive energy usage: " << plug.live << "kWh" << "\nHistoric energy usage: " << plug.historic << "kWh" << "\n";
	return os;
}
