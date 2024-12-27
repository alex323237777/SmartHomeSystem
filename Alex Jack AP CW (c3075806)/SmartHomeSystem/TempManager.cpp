#include "TempManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <numeric>

void TempManager::loadTempsFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::string line;
    bool isReadingTemps = false;

    while (std::getline(inFile, line))
    {
        if (line.empty() || line[0] == '#')
        {
            isReadingTemps = (line == "#Temps");
            continue;
        }

        if (isReadingTemps) {
            temps.push_back(Temp::fromFileString(line));
        }
    }
}

void TempManager::saveTempsToFile(const std::string& filename) const
{
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    outFile << "#Temps\n";
    for (const auto& temp : temps)
    {
        outFile << temp.toFileString() << "\n";
    }
}

void TempManager::displayTemps() const
{
    if (temps.empty())
    {
        std::cout << "No sensors available.\n";
        return;
    }

    for (const auto& temp : temps)
    {
        temp.displayDetails();
    }
}

void TempManager::quickview()
{
    std::string deviceName;
    std::cout << "Enter the name of the sensor: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    auto* temp = findTempByName(deviceName);
    if (temp)
    {
        temp->quickView();
    }
    else
    {
        std::cout << "Sensor not found.\n";
    }
}

void TempManager::addTemp()
{
    std::string name;
    double temperature, humidity, hisT, hisH;

    std::cout << "Enter the name of the sensor: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (const auto& temp : temps)
    {
        if (temp.getName() == name)
        {
            std::cout << "A sensor with this name already exists. Please choose a different name.\n";
            return;
        }
    }

    std::cout << "Enter the temperature (0 to 40): ";
    std::cin >> temperature;
    while (std::cin.fail() || temperature < 0 || temperature > 40)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid brightness percentage (0 to 40): ";
        std::cin >> temperature;
    }

    std::cout << "Enter the humidity level (0 to 100): ";
    std::cin >> humidity;
    while (std::cin.fail() || humidity < 0 || humidity > 100)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid brightness percentage (0 to 100): ";
        std::cin >> humidity;
    }
    // 7 day average used to calculate historic temperate and humidity values //
    std::cout << "Please enter each day's temperature reading from the last week (0-40): \n";
    std::vector<double> tempReadings; // vector for temperature inputs //
    for (int i = 0; i < 7; ++i) {
        double reading = 0; // initialises reading value //
        std::cout << "Day " << (i + 1) << ": ";
        while (!(std::cin >> reading) || reading < 0 || reading > 40) 
        { // error handling for the users input //
            std::cout << "Invalid input. Please enter a numeric value between 0 and 40: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        tempReadings.push_back(reading); // adds each value to the vector //
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    double totalTempUsage = std::accumulate(tempReadings.begin(), tempReadings.end(), 0.0); 
    hisT = totalTempUsage / tempReadings.size(); // calculates the average by using the total of all values and the size of the vector //
    // historic humidity readings are worked out in the same way as the temperate readings //
    std::cout << "Please enter each day's humidity reading from the last week (0-100): \n";
    std::vector<double> humidityReadings; 
    for (int i = 0; i < 7; ++i) {
        double reading = 0;
        std::cout << "Day " << (i + 1) << ": ";
        while (!(std::cin >> reading) || reading < 0 || reading > 100) 
        { 
            std::cout << "Invalid input. Please enter a numeric value between 0 and 100: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        humidityReadings.push_back(reading);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    double totalHumidityUsage = std::accumulate(humidityReadings.begin(), humidityReadings.end(), 0.0); 
    hisH = totalHumidityUsage / humidityReadings.size();

    Temp newTemp(name, temperature, humidity, hisT, hisH);
    temps.push_back(newTemp);

    std::cout << "Sensor added successfully!\n";

    saveTempsToFile("Temps.txt");
}

void TempManager::deleteTemp()
{
    std::string deviceName;
    std::string confirmDelete;
    bool deviceFound = false;

    std::cout << "Enter the name of the sensor you want to delete: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto it = temps.begin(); it != temps.end(); ++it)
    {
        if (it->getName() == deviceName)
        {
            deviceFound = true;

            std::cout << "Are you sure you want to delete the sensor '" << deviceName << "'? (Y/N): ";
            std::cin >> confirmDelete;
            std::cin.ignore();

            if (confirmDelete == "Y" || confirmDelete == "y")
            {
                temps.erase(it);
                std::cout << "Sensor '" << deviceName << "' has been deleted.\n";
            }
            else
            {
                std::cout << "Sensor deletion cancelled.\n";
            }
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << "Sensor with name '" << deviceName << "' not found.\n";
    }

    saveTempsToFile("Temps.txt");
}

void TempManager::updateTemp()
{
    std::string deviceName;
    std::string userChoice;
    bool deviceFound = false;

    std::cout << "Enter the name of the sensor you want to update: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto& temp : temps)
    {
        if (temp.getName() == deviceName)
        {
            deviceFound = true;
            std::cout << "You are about to update the light: " << deviceName << "\n";

            std::cout << "Do you want to update the Temperature? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                double newTemperature;
                std::cout << "Enter the new temperature level (0-40): ";
                std::cin >> newTemperature;
                while (std::cin.fail() || newTemperature < 0 || newTemperature > 40)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a value between 0 and 40: ";
                    std::cin >> newTemperature;
                }
                temp.setTemp(newTemperature);
            }

            std::cout << "Do you want to update the Humidity? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                double newHumidity;
                std::cout << "Enter the new humididty level (0-100): ";
                std::cin >> newHumidity;
                while (std::cin.fail() || newHumidity < 0 || newHumidity > 100)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a value between 0 and 100: ";
                    std::cin >> newHumidity;
                }
                temp.setHumid(newHumidity);
            }

            std::cout << "Do you want to update the historic temperature readings? (Y/N): \n";
            std::cin >> userChoice;
            std::cin.ignore(); // checks if the user wants to update the historic temperature readings //
            if (userChoice == "Y" || userChoice == "y")
            {
                std::cout << "Please enter each day's temperature reading from the last week (0-40): \n";
                std::vector<double> dailyReadings; // vector for user inputs //
                for (int i = 0; i < 7; ++i) // iterates through and asks user to input for each day //
                {
                    double reading = 0; // initialises reading value //
                    std::cout << "Day " << (i + 1) << ": ";
                    while (!(std::cin >> reading) || reading < 0 || reading > 40) 
                    { // error handling for incorrect data types, or values out of range //
                        std::cout << "Invalid input. Please enter a numeric value: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    dailyReadings.push_back(reading); // adds user input to the vector //
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                double totalUsage = std::accumulate(dailyReadings.begin(), dailyReadings.end(), 0.0);
                double averageUsage = totalUsage / dailyReadings.size();
                // calculates the average usage //
                temp.setHisT(averageUsage); // sets the historic reading as the updated value //
            }
            // humididty reading is updated in the same way as the temperature reading //
            std::cout << "Do you want to update the historic humidity usage? (Y/N): \n";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::cout << "Please enter each day's humidity reading from the last week (0-100): \n";
                std::vector<double> dailyReadings;
                for (int i = 0; i < 7; ++i) {
                    double reading = 0; 
                    std::cout << "Day " << (i + 1) << ": ";
                    while (!(std::cin >> reading) || reading < 0 || reading > 100) 
                    { 
                        std::cout << "Invalid input. Please enter a numeric value: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    dailyReadings.push_back(reading);
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                double totalUsage = std::accumulate(dailyReadings.begin(), dailyReadings.end(), 0.0);
                double averageUsage = totalUsage / dailyReadings.size();

                temp.setHisH(averageUsage);
            }




            std::cout << "The sensor has been updated successfully!\n";
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << "No sensor found with the name '" << deviceName << "'. Please check the name and try again.\n";
        return;
    }

    saveTempsToFile("Temps.txt");
}

Temp* TempManager::findTempByName(const std::string& name)
{
    for (auto& temp : temps)
    {
        if (temp.getName() == name)
        {
            return &temp;
        }
    }
    return nullptr;
}

void TempManager::syncWithDeviceManager(DeviceManager& manager)
{
    manager.getTemps().clear();
    for (const auto& temp : temps)
    {
        manager.addDevice(new Temp(temp));
    }
}

void TempManager::fetchFromDeviceManager(const DeviceManager& manager)
{
    temps.clear();
    for (const auto& temp : manager.getTemps())
    {
        temps.push_back(*temp);
    }
}
