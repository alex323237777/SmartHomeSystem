#ifndef THERMOSTATMANAGER_H
#define THERMOSTATMANAGER_H

#include "Thermostat.h"
#include "RadiatorManager.h" // include radiator manager for the heating boost function //
#include "DeviceManager.h"
#include <vector>
#include <string>

class ThermostatManager 
{
private:
    std::vector<Thermostat> thermostats; // vector of objects for thermostats //
    RadiatorManager* radiatorManager; // calls radiator manager for the heating boost //

    Thermostat* findThermostatByName(const std::string& name); // finds a specific thermostat by name //

public: //constructor to intialise the class and pass the address of radiator manager //
    ThermostatManager(RadiatorManager* radManager);

    void loadThermostatsFromFile(const std::string& filename); // loads thermostat information from the text file into the vector //
    void saveThermostatsToFile(const std::string& filename) const; // saves any changes made back to the text file //

    void displayThermostats() const;
    void quickview();
    void addThermostat(); // CRUD and quick view functions //
    void updateThermostat();
    void deleteThermostat();

    void activateHeatingBoost();

    void syncWithDeviceManager(DeviceManager& manager); // sync and update fucntions for device manager //
    void fetchFromDeviceManager(const DeviceManager& manager);
};

#endif


