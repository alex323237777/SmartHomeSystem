#ifndef LIGHTMANAGER_H // if header file is not defined //
#define LIGHTMANAGER_H // define the header file //

#include "Light.h"
#include "DeviceManager.h"
#include <vector>
#include <string>

class LightManager 
{
private:
    std::vector<Light> lights; // vector of objects to handle lights //

    Light* findLightByName(const std::string& name); // finds specific light based on its name //

public:
    void loadLightsFromFile(const std::string& filename); // loads lights from the text file //
    void saveLightsToFile(const std::string& filename) const; // saves lights back to the text file //

    void displayLights() const;
    void quickview();
    void addLight(); // methods for CRUD and quick view functions //
    void updateLight();
    void deleteLight();

    void syncWithDeviceManager(DeviceManager& manager); // syncs changes in light manager with the device manager  //
    void fetchFromDeviceManager(const DeviceManager& manager); // updates light manager with relevant devices from device manager //
};

#endif // ends the file guard //






