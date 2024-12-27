#include "RadiatorManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void RadiatorManager::loadRadiatorsFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::string line;
    bool isReadingRadiators = false;

    while (std::getline(inFile, line))
    {
        if (line.empty() || line[0] == '#')
        {
            isReadingRadiators = (line == "#Radiators");
            continue;
        }

        if (isReadingRadiators) {
            radiators.push_back(Radiator::fromFileString(line));
        }
    }
}

void RadiatorManager::saveRadiatorsToFile(const std::string& filename) const
{
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    outFile << "#Radiators\n";
    for (const auto& radiator : radiators)
    {
        outFile << radiator.toFileString() << "\n";
    }
}

void RadiatorManager::displayRadiators() const
{
    if (radiators.empty())
    {
        std::cout << "No radiators available.\n";
        return;
    }

    for (const auto& radiator : radiators)
    {
        radiator.displayDetails();
    }
}

void RadiatorManager::quickview()
{
    std::string deviceName;
    std::cout << "Enter the name of the radiator: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    auto* radiator = findRadiatorByName(deviceName);
    if (radiator)
    {
        radiator->quickView();
    }
    else
    {
        std::cout << "Radiator not found.\n";
    }
}

void RadiatorManager::addRadiator()
{
    std::string name, schedule;
    bool isOn;
    double temperature;

    std::cout << "Enter the name of the radiator: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (const auto& radiator : radiators)
    {
        if (radiator.getName() == name)
        {
            std::cout << "A radiator with this name already exists. Please choose a different name.\n";
            return;
        }
    }

    std::string onOffInput;
    std::cout << "Is the radiator on? (Y/N): ";
    std::cin >> onOffInput;
    isOn = (onOffInput == "Y" || onOffInput == "y");

    std::cout << "Enter temperature level (0 to 40): ";
    std::cin >> temperature;
    while (std::cin.fail() || temperature < 0 || temperature > 40)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid volume level (0 to 40): ";
        std::cin >> temperature;
    }

    std::cout << "Enter the schedule for when the radiator will next come on: ";
    std::cin.ignore();
    std::getline(std::cin, schedule);

    Radiator newRadiator(name, isOn, temperature, schedule);
    radiators.push_back(newRadiator);

    std::cout << "Radiator added successfully!\n";

    saveRadiatorsToFile("Radiators.txt");
}

void RadiatorManager::deleteRadiator()
{
    std::string deviceName;
    std::string confirmDelete;
    bool deviceFound = false;

    std::cout << "Enter the name of the radiator you want to delete: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto it = radiators.begin(); it != radiators.end(); ++it)
    {
        if (it->getName() == deviceName)
        {
            deviceFound = true;

            std::cout << "Are you sure you want to delete the radiator '" << deviceName << "'? (Y/N): ";
            std::cin >> confirmDelete;
            std::cin.ignore();

            if (confirmDelete == "Y" || confirmDelete == "y")
            {
                radiators.erase(it);
                std::cout << "Radiator '" << deviceName << "' has been deleted.\n";
            }
            else
            {
                std::cout << "Radiator deletion cancelled.\n";
            }
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << "Radiator with name '" << deviceName << "' not found.\n";
    }

    saveRadiatorsToFile("Radiators.txt");
}

void RadiatorManager::updateRadiator()
{
    std::string deviceName;
    std::string userChoice;
    bool deviceFound = false;

    std::cout << "Enter the name of the radiator you want to update: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto& radiator : radiators)
    {
        if (radiator.getName() == deviceName)
        {
            deviceFound = true;
            std::cout << "You are about to update the radiator: " << deviceName << "\n";

            std::cout << "Do you want to update the status of the radiator (On/Off)? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::string isOnChoice;
                std::cout << "Is the radiator on? (Y/N): ";
                std::cin >> isOnChoice;
                std::cin.ignore();
                radiator.setOn(isOnChoice == "Y" || isOnChoice == "y");
            }

            std::cout << "Do you want to adjust the temperature? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                double newTemp;
                std::cout << "Enter the new volume level (0-40): ";
                std::cin >> newTemp;
                while (std::cin.fail() || newTemp < 0 || newTemp > 40)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a value between 0 and 40: ";
                    std::cin >> newTemp;
                }
                radiator.setTemp(newTemp);
            }

            std::cout << "Do you want to update the schedule of the radiator? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::string newSchedule;
                std::cout << "Enter the new schedule of the radiator: ";
                std::getline(std::cin, newSchedule);
                radiator.setSchedule(newSchedule);
            }

            std::cout << "The radiator has been updated successfully!\n";
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << "No Radiator found with the name '" << deviceName << "'. Please check the name and try again.\n";
        return;
    }

    saveRadiatorsToFile("Radiators.txt");
}

void RadiatorManager::activateBoost() 
{ // function for activating the heating boost //
    for (auto& radiator : radiators) 
    { // checks through all radiators in the vector //
        radiator.setOn(true); // Turns all the radiators on //
        radiator.setSchedule("Heating boost active, heating on for the next hour");
    } // Changes the schedule message for all the radiators //

    saveRadiatorsToFile("Radiators.txt");
    // saves these changes to the radiator text file //
    std::cout << "Heating Boost activated: All radiators are on for the next hour.\n";
}


Radiator* RadiatorManager::findRadiatorByName(const std::string& name)
{
    for (auto& radiator : radiators)
    {
        if (radiator.getName() == name)
        {
            return &radiator;
        }
    }
    return nullptr;
}

void RadiatorManager::syncWithDeviceManager(DeviceManager& manager)
{
    manager.getRadiators().clear();
    for (const auto& radiator : radiators)
    {
        manager.addDevice(new Radiator(radiator));
    }
}

void RadiatorManager::fetchFromDeviceManager(const DeviceManager& manager)
{
    radiators.clear();
    for (const auto& radiator : manager.getRadiators())
    {
        radiators.push_back(*radiator);
    }
}
