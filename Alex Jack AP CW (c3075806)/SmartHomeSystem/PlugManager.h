#ifndef PLUGMANAGER_H
#define PLUGMANAGER_H

#include "Plug.h"
#include "DeviceManager.h"
#include <vector>
#include <string>

class PlugManager 
{
private:
    std::vector<Plug> plugs; // vector of objects to store the plugs

    Plug* findPlugByName(const std::string& name); // fucntion to find specific plug by name //

public:
    void loadPlugsFromFile(const std::string& filename); // loads plug info from the text file into the vector //
    void savePlugsToFile(const std::string& filename) const; // saves changes made in the code back to the text file //

    void displayPlugs() const;
    void quickview();
    void addPlug(); // CRUD and quick view functions //
    void updatePlug();
    void deletePlug();

    void syncWithDeviceManager(DeviceManager& manager); // sync and update fucntions for device manager //
    void fetchFromDeviceManager(const DeviceManager& manager);
};

#endif

