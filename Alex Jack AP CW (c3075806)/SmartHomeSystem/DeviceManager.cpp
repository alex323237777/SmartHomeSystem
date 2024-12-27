#include "DeviceManager.h"
#include <iostream>

DeviceManager::~DeviceManager()
{
    for (Device* device : devices)
    {
        delete device; // dynamically cleans up memory //
    }
}

void DeviceManager::addDevice(Device* device)
{
    devices.push_back(device); // adds a dynamically allocated device to the devices collection //
}

void DeviceManager::listDevices() const
{
    if (devices.empty())
    {
        std::cout << "No devices found.\n";
        return;
    }

    for (const auto& device : devices)
    {
        device->displayDetails(); // iterates through all devices in device and calls their display details method //
    }
}

std::vector<Light*> DeviceManager::getLights() const
{
    std::vector<Light*> lights;

    for (const auto& device : devices)
    {
        if (Light* light = dynamic_cast<Light*>(device)) // dynamic cast filters and picks out specific types of devices //
        {
            lights.push_back(light);
        }
    }

    return lights;
}

std::vector<Temp*> DeviceManager::getTemps() const
{
    std::vector<Temp*> temps;

    for (const auto& device : devices)
    {
        if (Temp* temp = dynamic_cast<Temp*>(device))
        {
            temps.push_back(temp);
        }
    }

    return temps;
}
std::vector<Speaker*> DeviceManager::getSpeakers() const
{
    std::vector<Speaker*> speakers;

    for (const auto& device : devices)
    {
        if (Speaker* speaker = dynamic_cast<Speaker*>(device))
        {
            speakers.push_back(speaker);
        }
    }

    return speakers;
}

std::vector<Plug*> DeviceManager::getPlugs() const
{
    std::vector<Plug*> plugs;

    for (const auto& device : devices)
    {
        if (Plug* plug = dynamic_cast<Plug*>(device))
        {
            plugs.push_back(plug);
        }
    }

    return plugs;
}

std::vector<Radiator*> DeviceManager::getRadiators() const
{
    std::vector<Radiator*> radiators;
    {
        for (const auto& device : devices)
        {
            if (Radiator* radiator = dynamic_cast<Radiator*>(device))
            {
                radiators.push_back(radiator);
            }
        }
    }
    return radiators;
}

std::vector<Thermostat*> DeviceManager::getThermostats() const
{
    std::vector<Thermostat*> thermostats;
    {
        for (const auto& device : devices)
        {
            if (Thermostat* thermostat = dynamic_cast<Thermostat*>(device))
            {
                thermostats.push_back(thermostat);
            }
        }
    }
    return thermostats;
}


