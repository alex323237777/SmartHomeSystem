#ifndef DEVICEMANAGER_H  
#define DEVICEMANAGER_H

#include "Device.h"
#include "Light.h"  
#include "Temp.h"   
#include "Plug.h"
#include "Speaker.h" // include all device class headers //
#include "Radiator.h"
#include "Thermostat.h"
#include <vector>
#include <string>

class DeviceManager 
{
private:
    std::vector<Device*> devices; // this class handles dynamic storage of devices //

public:
    ~DeviceManager();
    void addDevice(Device* device);
    void listDevices() const;
    std::vector<Light*> getLights() const; // handles storage and retrieval for each type of device //
    std::vector<Temp*> getTemps() const;
    std::vector<Speaker*> getSpeakers() const;
    std::vector<Plug*> getPlugs() const;
    std::vector<Radiator*> getRadiators() const;
    std::vector<Thermostat*> getThermostats() const;
};

#endif



