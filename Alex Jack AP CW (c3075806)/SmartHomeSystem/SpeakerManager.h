#ifndef SPEAKERMANAGER_H
#define SPEAKERMANAGER_H

#include "Speaker.h"
#include "DeviceManager.h"
#include <vector>
#include <string>

class SpeakerManager 
{
private:
    std::vector<Speaker> speakers; // vector of objects for speakers //

    Speaker* findSpeakerByName(const std::string& name); // finds a specific speaker by name //

public:
    void loadSpeakersFromFile(const std::string& filename); // loads the values from the text file into the vector //
    void saveSpeakersToFile(const std::string& filename) const; // saves the changes to the values back to the text file //

    void displaySpeakers() const;
    void quickview();
    void addSpeaker(); // CRUD and quick view functions //
    void updateSpeaker();
    void deleteSpeaker();

    void syncWithDeviceManager(DeviceManager& manager); // sync and update fucntions for device manager //
    void fetchFromDeviceManager(const DeviceManager& manager);
};

#endif

