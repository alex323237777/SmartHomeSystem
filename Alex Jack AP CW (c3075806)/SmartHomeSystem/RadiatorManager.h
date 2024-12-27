#ifndef RADIATORMANAGER_H
#define RADIATORMANAGER_H

#include "Radiator.h"
#include "DeviceManager.h"
#include <vector>
#include <string>

class RadiatorManager 
{
private:
    std::vector<Radiator> radiators; // vector of objects to store radiator objects //

    Radiator* findRadiatorByName(const std::string& name); // finds a specific radiator by name //

public:
    void loadRadiatorsFromFile(const std::string& filename); // loads radiator info from the text file //
    void saveRadiatorsToFile(const std::string& filename) const; // saves changes back to the text file //

    void displayRadiators() const;
    void quickview();
    void addRadiator(); // CRUD and quick view functions //
    void updateRadiator();
    void deleteRadiator();

    void activateBoost(); // activates the heating boost(turns all radiators on and changes schedule message)

    void syncWithDeviceManager(DeviceManager& manager); // sync and update fucntions for device manager //
    void fetchFromDeviceManager(const DeviceManager& manager);
};

#endif


