#include "Temp.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Temp::Temp(const std::string& tempName, double temperatureLevel, double humidityLevel, double hisTempL, double hisHumidL)
	: Device(tempName), temperature(temperatureLevel), humidity(humidityLevel), hisT(hisTempL), hisH(hisHumidL) {}

void Temp::quickView() const
{
	std::cout << *this;
}

void Temp::displayDetails() const
{
	std::cout << *this;
}

std::string Temp::toFileString() const
{
	std::ostringstream ss;
	ss << name << "," << temperature << "," << humidity << "," << hisT << "," << hisH;
	return ss.str();
}

Temp Temp::fromFileString(const std::string& data)
{
	std::istringstream ss(data);
	std::string name;
	double temperature, humidity, hisT, hisH;

	std::getline(ss, name, ',');
	ss >> temperature;
	ss.ignore();
	ss >> humidity;
	ss.ignore();
	ss >> hisT;
	ss.ignore();
	ss >> hisH;

	return Temp(name, temperature, humidity, hisT, hisH);
}

std::ostream& operator<<(std::ostream& os, const Temp& temp)
{
	os << "\nSensor: " << temp.name << "\nTemperature: " << temp.temperature << "c" << "\nHumidity: " << temp.humidity << "%" << "\nLast weeks average temperature: " << temp.hisT <<  "\nLast weeks average humidity level: " << temp.hisH << "\n";
	return os;
}
