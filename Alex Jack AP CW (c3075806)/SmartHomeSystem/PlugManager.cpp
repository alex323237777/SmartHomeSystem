#include "PlugManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <numeric>

void PlugManager::loadPlugsFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::string line;
    bool isReadingPlugs = false;

    while (std::getline(inFile, line))
    {
        if (line.empty() || line[0] == '#')
        {
            isReadingPlugs = (line == "#Plugs");
            continue;
        }

        if (isReadingPlugs) {
            plugs.push_back(Plug::fromFileString(line));
        }
    }
}

void PlugManager::savePlugsToFile(const std::string& filename) const
{
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    outFile << "#Plugs\n";
    for (const auto& plug : plugs)
    {
        outFile << plug.toFileString() << "\n";
    }
}

void PlugManager::displayPlugs() const
{
    if (plugs.empty())
    {
        std::cout << "No plugs available.\n";
        return;
    }

    for (const auto& plug : plugs)
    {
        plug.displayDetails();
    }
}

void PlugManager::quickview()
{
    std::string deviceName;
    std::cout << "Enter the name of the plug: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    auto* plug = findPlugByName(deviceName);
    if (plug)
    {
        plug->quickView();
    }
    else
    {
        std::cout << "Plug not found.\n";
    }
}

void PlugManager::addPlug()
{
    std::string name;
    bool isOn;
    double live, historic;

    std::cout << "Enter the name of the plug: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (const auto& plug : plugs)
    {
        if (plug.getName() == name)
        {
            std::cout << "A plug with this name already exists. Please choose a different name.\n";
            return;
        }
    }

    std::string onOffInput;
    std::cout << "Is the plug on? (Y/N): ";
    std::cin >> onOffInput;
    isOn = (onOffInput == "Y" || onOffInput == "y");

    std::cout << "Enter todays energy usage, kWh (0 to 100): ";
    std::cin >> live;
    while (std::cin.fail() || live < 0 || live > 100)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please use a valid entry (0 to 100): ";
        std::cin >> live;
    }
    // calculates historic energy usage by using a 7 day average based on user input //
    std::cout << "Please enter each days energy reading from the last week(0-100): \n";
    std::vector<double> dailyReadings; // creates a vector to store the user inputs //
    for (int i = 0; i < 7; ++i) {
        double reading = 0; // askes the user for an input for each day of the previous week //
        std::cout << "Day " << (i + 1) << ": ";
        while (!(std::cin >> reading) || reading < 0 || reading > 100) {
            std::cout << "Invalid input. Please enter a valid numeric value: ";
            std::cin.clear(); // handles error handling for user input //
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        dailyReadings.push_back(reading); // adds the user input to the vector //
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    double totalUsage = std::accumulate(dailyReadings.begin(), dailyReadings.end(), 0.0);
    historic = totalUsage / dailyReadings.size(); // works out the total usage through totalusage and count values //

    Plug newPlug(name, isOn, live, historic);
    plugs.push_back(newPlug);

    std::cout << "Plug added successfully!\n";

    savePlugsToFile("Plugs.txt");
}

void PlugManager::deletePlug()
{
    std::string deviceName;
    std::string confirmDelete;
    bool deviceFound = false;

    std::cout << "Enter the name of the plug you want to delete: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto it = plugs.begin(); it != plugs.end(); ++it)
    {
        if (it->getName() == deviceName)
        {
            deviceFound = true;

            std::cout << "Are you sure you want to delete the plug '" << deviceName << "'? (Y/N): ";
            std::cin >> confirmDelete;
            std::cin.ignore();

            if (confirmDelete == "Y" || confirmDelete == "y")
            {
                plugs.erase(it);
                std::cout << "Plug '" << deviceName << "' has been deleted.\n";
            }
            else
            {
                std::cout << "Plug deletion cancelled.\n";
            }
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << " with name '" << deviceName << "' not found.\n";
    }

    savePlugsToFile("Plugs.txt");
}

void PlugManager::updatePlug()
{
    std::string deviceName;
    std::string userChoice;
    bool deviceFound = false;

    std::cout << "Enter the name of the plug you want to update: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto& plug : plugs)
    {
        if (plug.getName() == deviceName)
        {
            deviceFound = true;
            std::cout << "You are about to update the plug: " << deviceName << "\n";

            std::cout << "Do you want to update the status of the plug (On/Off)? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::string isOnChoice;
                std::cout << "Is the plug ON? (Y/N): ";
                std::cin >> isOnChoice;
                std::cin.ignore();
                plug.setOn(isOnChoice == "Y" || isOnChoice == "y");
            }

            std::cout << "Do you want to update the live kWh of the plug? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                double newLive;
                std::cout << "Enter the new energy usage level (0-100): ";
                std::cin >> newLive;
                while (std::cin.fail() || newLive < 0 || newLive > 100)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a value between 0 and 100: ";
                    std::cin >> newLive;
                }
                plug.setLive(newLive);
            }
            // updates the historic data using the same process from the add function //
            std::cout << "Do you want to update the historic data usage? (Y/N): \n";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::cout << "Please enter each days energy reading from the last week(0-100) : \n";
                std::vector<double> dailyReadings;
                for (int i = 0; i < 7; ++i) {
                    double reading = 0; // intialise the reading value //
                    std::cout << "Day " << (i + 1) << ": ";
                    while (!(std::cin >> reading) || reading < 0 || reading > 100) {
                        std::cout << "Invalid input. Please enter a valid numeric value: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    dailyReadings.push_back(reading);
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                double totalUsage = std::accumulate(dailyReadings.begin(), dailyReadings.end(), 0.0);
                double averageUsage = totalUsage / dailyReadings.size();

                plug.setHistoric(averageUsage);
            }

            std::cout << "The plug has been updated successfully!\n";
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << "No plug found with the name '" << deviceName << "'. Please check the name and try again.\n";
        return;
    }

    savePlugsToFile("Plugs.txt");
}

Plug* PlugManager::findPlugByName(const std::string& name)
{
    for (auto& plug : plugs)
    {
        if (plug.getName() == name)
        {
            return &plug;
        }
    }
    return nullptr;
}

void PlugManager::syncWithDeviceManager(DeviceManager& manager)
{
    manager.getPlugs().clear();
    for (const auto& plug : plugs)
    {
        manager.addDevice(new Plug(plug));
    }
}

void PlugManager::fetchFromDeviceManager(const DeviceManager& manager)
{
    plugs.clear();
    for (const auto& plug : manager.getPlugs())
    {
        plugs.push_back(*plug);
    }
}