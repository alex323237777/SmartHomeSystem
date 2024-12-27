#include "Radiator.h"
#include <iostream>
#include <sstream>

Radiator::Radiator(const std::string& radiatorName, bool radiatorOn, double temperatureLevel, const std::string& radiatorSchedule)
    : Device(radiatorName), isOn(radiatorOn), temperature(temperatureLevel), schedule(radiatorSchedule) {}

void Radiator::quickView() const {
    std::cout << *this;
}

void Radiator::displayDetails() const {
    std::cout << *this;
}

std::string Radiator::toFileString() const {
    std::ostringstream ss;
    ss << name << "," << isOn << "," << temperature << "," << schedule;
    return ss.str();
}

Radiator Radiator::fromFileString(const std::string& data) {
    std::istringstream ss(data);
    std::string name, schedule;
    bool isOn;
    int targetTemp;

    std::getline(ss, name, ',');
    ss >> isOn;
    ss.ignore();
    ss >> targetTemp;
    ss.ignore();
    std::getline(ss, schedule);

    return Radiator(name, isOn, targetTemp, schedule);
}

std::ostream& operator<<(std::ostream& os, const Radiator& radiator) {
    os << "\nRadiator: " << radiator.name
        << "\nStatus: " << (radiator.isOn ? "On" : "Off")
        << "\nTarget Temperature: " << radiator.temperature
        << "\nSchedule: " << radiator.schedule << "\n";
    return os;
}
