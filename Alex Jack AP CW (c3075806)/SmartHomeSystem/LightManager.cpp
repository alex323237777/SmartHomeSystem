#include "LightManager.h"
#include <fstream> // allows both reading and writing to a file //
#include <sstream> // allows functionality for string based streams //
#include <iostream> // allows functionality for standard I/O streams //

void LightManager::loadLightsFromFile(const std::string& filename) 
{ // function to lights from the text file into the vector off objects //
    std::ifstream inFile(filename);
    if (!inFile.is_open()) 
    { // checks if a text file for lights exists //
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::string line;
    bool isReadingLights = false; // checks if the code is already reading from the file //

    while (std::getline(inFile, line)) 
    {
        if (line.empty() || line[0] == '#') 
        {
            isReadingLights = (line == "#Lights");
            continue; // finds the text file with the correct information //
        }

        if (isReadingLights) { // calls fromFileString to turn the text information into an object in memory //
            lights.push_back(Light::fromFileString(line)); // pushes the information onto the light vector //
        }
    }
}

void LightManager::saveLightsToFile(const std::string& filename) const 
{ // fucntion to save changes made to the light objects, whilst the code is running, back to the text file //
    std::ofstream outFile(filename, std::ios::trunc); // overrides a records old data when the file is being updated //
    if (!outFile.is_open()) 
    { // checks if the file can be opened //
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    outFile << "#Lights\n"; // calls the correct text file or light objects //
    for (const auto& light : lights) 
    {
        outFile << light.toFileString() << "\n";
    } // calls toFileString to serialise the light values for the text file //
}

void LightManager::displayLights() const 
{
    if (lights.empty()) 
    { // error message if there is no lights to display //
        std::cout << "No lights available.\n";
        return;
    }

    for (const auto& light : lights) 
    {
        light.displayDetails(); // calls display details function //
    }
}

void LightManager::quickview() 
{
    std::string deviceName;
    std::cout << "Enter the name of the light: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);
    // calls findLightByName to get a specific lights information /
    auto* light = findLightByName(deviceName);
    if (light) 
    {
        light->quickView(); // pointer to call quick view //
    }
    else 
    { // error message if incorrect light message is not found //
        std::cout << "Light not found.\n";
    }
}

void LightManager::addLight() 
{
    std::string name, sleepTimer;
    bool isOn; // values for creating a new record //
    double brightness;

    std::cout << "Enter the name of the light: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (const auto& light : lights) 
    {
        if (light.getName() == name) 
        { // checks if a light by that name already exists //
            std::cout << "A light with this name already exists. Please choose a different name.\n";
            return;
        }
    }

    std::string onOffInput;
    std::cout << "Is the light on? (Y/N): ";
    std::cin >> onOffInput;
    isOn = (onOffInput == "Y" || onOffInput == "y");

    std::cout << "Enter brightness percentage (0 to 100): ";
    std::cin >> brightness; // makes sure the value is in the accepted range //
    while (std::cin.fail() || brightness < 0 || brightness > 100) 
    {
        std::cin.clear(); // checks if the input is in the correct format //
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid brightness percentage (0 to 100): ";
        std::cin >> brightness;
    }

    std::cout << "Enter the sleep timer (e.g., 09:00 AM): ";
    std::cin.ignore();
    std::getline(std::cin, sleepTimer);

    Light newLight(name, isOn, brightness, sleepTimer); // creates new light object with entered values //
    lights.push_back(newLight); // adds this new record to the light vector of objects //

    std::cout << "Light added successfully!\n";

    saveLightsToFile("Devices.txt"); // calls to save to file to ensure these changes are correctly applied //
}

void LightManager::deleteLight() 
{
    std::string deviceName;
    std::string confirmDelete;
    bool deviceFound = false;

    std::cout << "Enter the name of the light you want to delete: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto it = lights.begin(); it != lights.end(); ++it) 
    {
        if (it->getName() == deviceName) // finds the device based on name input //
        {
            deviceFound = true;
            // asks the user if they are sure about deletion //
            std::cout << "Are you sure you want to delete the light '" << deviceName << "'? (Y/N): ";
            std::cin >> confirmDelete;
            std::cin.ignore();

            if (confirmDelete == "Y" || confirmDelete == "y")
            { // checks response and if Yes deletes the record //
                lights.erase(it); // removes the record from the light record //
                std::cout << "Light '" << deviceName << "' has been deleted.\n";
            }
            else 
            { 
                std::cout << "Light deletion cancelled.\n";
            }
            break;
        }
    }

    if (!deviceFound) 
    { // error message if invalid light name is entered //
        std::cout << "Light with name '" << deviceName << "' not found.\n";
    }

    saveLightsToFile("Devices.txt"); // calls save to file to ensure changes are carried out //
}

void LightManager::updateLight() 
{
    std::string deviceName;
    std::string userChoice; // input for confirmation of which updates the user wants to do //
    bool deviceFound = false;

    std::cout << "Enter the name of the light you want to update: ";
    std::cin.ignore(); // clears the input buffer, which allows the system to move onto the next input //
    std::getline(std::cin, deviceName); // get line prepares system for next input //

    for (auto& light : lights) // checks through the light vector for that specific record //
    {
        if (light.getName() == deviceName) 
        {
            deviceFound = true;
            std::cout << "You are about to update the light: " << deviceName << "\n";

            std::cout << "Do you want to update the status of the light (On/Off)? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore(); // clears the input buffer, which allows the system to move onto the next input //
            if (userChoice == "Y" || userChoice == "y")
            {
                std::string isOnChoice;
                std::cout << "Is the light ON? (Y/N): ";
                std::cin >> isOnChoice;
                std::cin.ignore();
                light.setOn(isOnChoice == "Y" || isOnChoice == "y");
            } // sets new choice //

            std::cout << "Do you want to update the brightness? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                double newBrightness;
                std::cout << "Enter the new brightness percentage (0-100): ";
                std::cin >> newBrightness;
                while (std::cin.fail() || newBrightness < 0 || newBrightness > 100) 
                { // checks the value is in the accepted range //
                    std::cin.clear(); // checks that the input is in the correct format //
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a value between 0 and 100: ";
                    std::cin >> newBrightness;
                }
                light.setBrightness(newBrightness);
            } // sets brightness as updated value //

            std::cout << "Do you want to update the sleep timer? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::string newSleepTimer;
                std::cout << "Enter the new sleep timer (e.g., 10:00 PM): ";
                std::getline(std::cin, newSleepTimer);
                light.setSleepTimer(newSleepTimer);
            } // sets sleep timer as updated value //

                std::cout << "The light has been updated successfully!\n";
            break;
        }
    }

    if (!deviceFound) 
    { // error message if the light name input is an invalid value //
        std::cout << "No light found with the name '" << deviceName << "'. Please check the name and try again.\n";
        return;
    }

    saveLightsToFile("Devices.txt"); // calls save to file to ensure updates are successfully carried out //
}

Light* LightManager::findLightByName(const std::string& name) 
{
    for (auto& light : lights) 
    {
        if (light.getName() == name) // finds light based on its name by extracting name from the light vector //
        {
            return &light;
        }
    }
    return nullptr; // returns nullptr if no light can be find //
}

void LightManager::syncWithDeviceManager(DeviceManager& manager) 
{ // updates devicemanager instance with the light information, to ensure both managers have consistent data //
    manager.getLights().clear(); 
    for (const auto& light : lights) 
    {
        manager.addDevice(new Light(light)); 
    }
}

void LightManager::fetchFromDeviceManager(const DeviceManager& manager) 
{
    lights.clear(); 
    for (const auto& light : manager.getLights()) 
    { // updates light manager with the information from device manager //
        lights.push_back(*light); 
    }
}










