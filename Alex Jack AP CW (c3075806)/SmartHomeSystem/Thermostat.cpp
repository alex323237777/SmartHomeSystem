#include "Thermostat.h"
#include <iostream>
#include <sstream>

Thermostat::Thermostat(const std::string& thermostatName, bool thermostatOn, const std::string& thermostatSchedule)
    : Device(thermostatName), isOn(thermostatOn), schedule(thermostatSchedule) {}

void Thermostat::quickView() const {
    std::cout << *this;
}

void Thermostat::displayDetails() const {
    std::cout << *this;
}

std::string Thermostat::toFileString() const {
    std::ostringstream ss;
    ss << name << "," << isOn << "," << schedule;
    return ss.str();
}

Thermostat Thermostat::fromFileString(const std::string& data) {
    std::istringstream ss(data);
    std::string name, schedule;
    bool isOn;

    std::getline(ss, name, ',');
    ss >> isOn;
    ss.ignore();
    std::getline(ss, schedule);

    return Thermostat(name, isOn, schedule);
}

void Thermostat::activateHeatingBoost() {
    std::cout << "Activating heating boost for thermostat '" << name << "'.\n";
    schedule = "Heating boost activated, heating on for next hour.";
    isOn = true;
}

std::ostream& operator<<(std::ostream& os, const Thermostat& thermostat) {
    os << "\nThermostat: " << thermostat.name
        << "\nStatus: " << (thermostat.isOn ? "On" : "Off")
        << "\nSchedule: " << thermostat.schedule << "\n";
    return os;
}

