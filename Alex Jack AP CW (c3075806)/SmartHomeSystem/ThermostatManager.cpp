#include "ThermostatManager.h"
#include "RadiatorManager.h" // includes radiator manager for the heating boost function //
#include <fstream>
#include <sstream>
#include <iostream>
// links to radiator manager to allow the heating boost function to be carried out correctly //
ThermostatManager::ThermostatManager(RadiatorManager* radManager) : radiatorManager(radManager) {}

void ThermostatManager::loadThermostatsFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::string line;
    bool isReadingThermostats = false;

    while (std::getline(inFile, line))
    {
        if (line.empty() || line[0] == '#')
        {
            isReadingThermostats = (line == "#Thermostats");
            continue;
        }

        if (isReadingThermostats) {
            thermostats.push_back(Thermostat::fromFileString(line));
        }
    }
}

void ThermostatManager::saveThermostatsToFile(const std::string& filename) const
{
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    outFile << "#Thermostats\n";
    for (const auto& thermostat : thermostats)
    {
        outFile << thermostat.toFileString() << "\n";
    }
}

void ThermostatManager::displayThermostats() const
{
    if (thermostats.empty())
    {
        std::cout << "No devices available.\n";
        return;
    }

    for (const auto& thermostat : thermostats)
    {
        thermostat.displayDetails();
    }
}

void ThermostatManager::quickview()
{
    std::string deviceName;
    std::cout << "Enter the name of the device: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    auto* thermostat = findThermostatByName(deviceName);
    if (thermostat)
    {
        thermostat->quickView();
    }
    else
    {
        std::cout << "Device not found.\n";
    }
}

void ThermostatManager::addThermostat()
{
    std::string name, schedule;
    bool isOn;

    std::cout << "Enter the name of the device: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (const auto& thermostat : thermostats)
    {
        if (thermostat.getName() == name)
        {
            std::cout << "A device with this name already exists. Please choose a different name.\n";
            return;
        }
    }

    std::string onOffInput;
    std::cout << "Is the device on? (Y/N): ";
    std::cin >> onOffInput;
    isOn = (onOffInput == "Y" || onOffInput == "y");

    std::cout << "Enter the schedule for when the device will next come on: ";
    std::cin.ignore();
    std::getline(std::cin, schedule);

    Thermostat newThermostat(name, isOn, schedule);
    thermostats.push_back(newThermostat);

    std::cout << "Device added successfully!\n";

    saveThermostatsToFile("Thermostats.txt");
}

void ThermostatManager::deleteThermostat()
{
    std::string deviceName;
    std::string confirmDelete;
    bool deviceFound = false;

    std::cout << "Enter the name of the device you want to delete: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto it = thermostats.begin(); it != thermostats.end(); ++it)
    {
        if (it->getName() == deviceName)
        {
            deviceFound = true;

            std::cout << "Are you sure you want to delete the device '" << deviceName << "'? (Y/N): ";
            std::cin >> confirmDelete;
            std::cin.ignore();

            if (confirmDelete == "Y" || confirmDelete == "y")
            {
                thermostats.erase(it);
                std::cout << "Device '" << deviceName << "' has been deleted.\n";
            }
            else
            {
                std::cout << "Device deletion cancelled.\n";
            }
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << "Device with name '" << deviceName << "' not found.\n";
    }

    saveThermostatsToFile("Thermostats.txt");
}

void ThermostatManager::updateThermostat()
{
    std::string deviceName;
    std::string userChoice;
    bool deviceFound = false;

    std::cout << "Enter the name of the device you want to update: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto& thermostat : thermostats)
    {
        if (thermostat.getName() == deviceName)
        {
            deviceFound = true;
            std::cout << "You are about to update the device: " << deviceName << "\n";

            std::cout << "Do you want to update the status of the device (On/Off)? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::string isOnChoice;
                std::cout << "Is the radiator on? (Y/N): ";
                std::cin >> isOnChoice;
                std::cin.ignore();
                thermostat.setOn(isOnChoice == "Y" || isOnChoice == "y");
            }

            std::cout << "Do you want to update the schedule of the device? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::string newSchedule;
                std::cout << "Enter the new schedule of the device: ";
                std::getline(std::cin, newSchedule);
                thermostat.setSchedule(newSchedule);
            }

            std::cout << "The radiator has been updated successfully!\n";
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << "No Device found with the name '" << deviceName << "'. Please check the name and try again.\n";
        return;
    }

    saveThermostatsToFile("Thermostats.txt");
}

void ThermostatManager::activateHeatingBoost() 
{ // function to activate the heating boost when requested, via the thermostat menu //
    if (radiatorManager) 
    { // pointer to the function in radiator manager to apply the needed changes //
        radiatorManager->loadRadiatorsFromFile("Radiators.txt"); // loads radiator text files so that data is not overriden if this function is called before any radiator ones //
        radiatorManager->activateBoost(); // calls the appropriate function //
    }
    else 
    { // error message if not needed //
        std::cerr << "Error: Radiator Manager is not initialized.\n";
    }
}


Thermostat* ThermostatManager::findThermostatByName(const std::string& name)
{
    for (auto& thermostat : thermostats)
    {
        if (thermostat.getName() == name)
        {
            return &thermostat;
        }
    }
    return nullptr;
}

void ThermostatManager::syncWithDeviceManager(DeviceManager& manager)
{
    manager.getThermostats().clear();
    for (const auto& thermostat : thermostats)
    {
        manager.addDevice(new Thermostat(thermostat));
    }
}

void ThermostatManager::fetchFromDeviceManager(const DeviceManager& manager)
{
    thermostats.clear();
    for (const auto& thermostat : manager.getThermostats())
    {
        thermostats.push_back(*thermostat);
    }
}
