	#include "Light.h"
	#include <iostream>
	#include <sstream>
	#include <stdexcept>

	Light::Light(const std::string& lightName, bool isLightOn, double brightnessLevel, const std::string& timer)
		: Device(lightName), isOn(isLightOn), brightness(brightnessLevel), sleepTimer(timer) {}
	// constructor, that calls the base device class for device name, as well as including the light values //
	void Light::quickView() const 
	{
		std::cout << *this; 
	}
	// redirects these 2 methods for the outputs, done via operater overloading //
	void Light::displayDetails() const 
	{
		std::cout << *this; 
	}

	std::string Light::toFileString() const 
	{
		std::ostringstream ss; // serialises the light values, ready for saving them to the text file //
		ss << name << "," << isOn << "," << brightness << "," << sleepTimer;
		return ss.str(); // seperates each value with a comma so that its in the right format for the text file //
	}

	Light Light::fromFileString(const std::string& data) 
	{ // deserialises the information, so its ready to be turned into an object //
		std::istringstream ss(data); // parses the string, and turns the values into the right format //
		std::string name, timer;
		bool isOn;
		double brightness;

		std::getline(ss, name, ',');
		ss >> isOn;
		ss.ignore();
		ss >> brightness;
		ss.ignore();
		std::getline(ss, timer);

		return Light(name, isOn, brightness, timer); // returns finished object with each values as the correct data type //
	}

	std::ostream& operator<<(std::ostream& os, const Light& light) 
	{ // overloads the operater to output device information for quick view and display methods //
		os << "\nLight: " << light.name << "\nStatus: " << (light.isOn ? "On" : "Off") << "\nBrightness: " << light.brightness << "%" << "\nSleep Timer: " << light.sleepTimer << "\n";
		return os;
	}









