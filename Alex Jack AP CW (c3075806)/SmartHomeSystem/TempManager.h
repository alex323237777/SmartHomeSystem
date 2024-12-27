#ifndef TEMPMANAGER_H
#define TEMPMANAGER_H

#include "Temp.h"
#include "DeviceManager.h"
#include <vector>
#include <string>

class TempManager 
{
private:
    std::vector<Temp> temps; // vector of objects for temperate and humidity sensors //

    Temp* findTempByName(const std::string& name); // finds a specific sensor by name //

public:
    void loadTempsFromFile(const std::string& filename); // loads the information from the text file into the vector //
    void saveTempsToFile(const std::string& filename) const; // saves changes made whilst the code is running back to the text file //

    void displayTemps() const;
    void quickview();
    void addTemp(); // CRUD and quick view functions //
    void updateTemp();
    void deleteTemp();

    void syncWithDeviceManager(DeviceManager& manager); // sync and update fucntions for device manager //
    void fetchFromDeviceManager(const DeviceManager& manager);
};

#endif
