#include "SpeakerManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void SpeakerManager::loadSpeakersFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::string line;
    bool isReadingSpeakers = false;

    while (std::getline(inFile, line))
    {
        if (line.empty() || line[0] == '#')
        {
            isReadingSpeakers = (line == "#Speakers");
            continue;
        }

        if (isReadingSpeakers) {
            speakers.push_back(Speaker::fromFileString(line));
        }
    }
}

void SpeakerManager::saveSpeakersToFile(const std::string& filename) const
{
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    outFile << "#Speakers\n";
    for (const auto& speaker : speakers)
    {
        outFile << speaker.toFileString() << "\n";
    }
}

void SpeakerManager::displaySpeakers() const
{
    if (speakers.empty())
    {
        std::cout << "No speakers available.\n";
        return;
    }

    for (const auto& speaker : speakers)
    {
        speaker.displayDetails();
    }
}

void SpeakerManager::quickview()
{
    std::string deviceName;
    std::cout << "Enter the name of the speaker: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    auto* speaker = findSpeakerByName(deviceName);
    if (speaker)
    {
        speaker->quickView();
    }
    else
    {
        std::cout << "Speaker not found.\n";
    }
}

void SpeakerManager::addSpeaker()
{
    std::string name, song;
    bool isPlaying;
    double volume;

    std::cout << "Enter the name of the speaker: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (const auto& speaker : speakers)
    {
        if (speaker.getName() == name)
        {
            std::cout << "A speaker with this name already exists. Please choose a different name.\n";
            return;
        }
    }

    std::string onOffInput;
    std::cout << "Is the speaker on? (Y/N): ";
    std::cin >> onOffInput;
    isPlaying = (onOffInput == "Y" || onOffInput == "y");

    std::cout << "Enter volume level (0 to 100): ";
    std::cin >> volume;
    while (std::cin.fail() || volume < 0 || volume > 100)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid volume level (0 to 100): ";
        std::cin >> volume;
    }

    std::cout << "Enter the song title: ";
    std::cin.ignore();
    std::getline(std::cin, song);

    Speaker newSpeaker(name, isPlaying, volume, song);
    speakers.push_back(newSpeaker);

    std::cout << "Speaker added successfully!\n";

    saveSpeakersToFile("Speakers.txt");
}

void SpeakerManager::deleteSpeaker()
{
    std::string deviceName;
    std::string confirmDelete;
    bool deviceFound = false;

    std::cout << "Enter the name of the speaker you want to delete: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto it = speakers.begin(); it != speakers.end(); ++it)
    {
        if (it->getName() == deviceName)
        {
            deviceFound = true;

            std::cout << "Are you sure you want to delete the speaker '" << deviceName << "'? (Y/N): ";
            std::cin >> confirmDelete;
            std::cin.ignore();

            if (confirmDelete == "Y" || confirmDelete == "y")
            {
                speakers.erase(it);
                std::cout << "Speaker '" << deviceName << "' has been deleted.\n";
            }
            else
            {
                std::cout << "Speaker deletion cancelled.\n";
            }
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << "Speaker with name '" << deviceName << "' not found.\n";
    }

    saveSpeakersToFile("Speakers.txt");
}

void SpeakerManager::updateSpeaker()
{
    std::string deviceName;
    std::string userChoice;
    bool deviceFound = false;

    std::cout << "Enter the name of the speaker you want to update: ";
    std::cin.ignore();
    std::getline(std::cin, deviceName);

    for (auto& speaker : speakers)
    {
        if (speaker.getName() == deviceName)
        {
            deviceFound = true;
            std::cout << "You are about to update the speaker: " << deviceName << "\n";

            std::cout << "Do you want to update the status of the light (Play/Pause)? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::string isOnChoice;
                std::cout << "Is the speaker playing? (Y/N): ";
                std::cin >> isOnChoice;
                std::cin.ignore();
                speaker.setPlaying(isOnChoice == "Y" || isOnChoice == "y");
            }

            std::cout << "Do you want to adjust the volume? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                double newVolume;
                std::cout << "Enter the new volume level (0-100): ";
                std::cin >> newVolume;
                while (std::cin.fail() || newVolume < 0 || newVolume > 100)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a value between 0 and 100: ";
                    std::cin >> newVolume;
                }
                speaker.setVolume(newVolume);
            }

            std::cout << "Do you want to update the song that's playing? (Y/N): ";
            std::cin >> userChoice;
            std::cin.ignore();
            if (userChoice == "Y" || userChoice == "y")
            {
                std::string newSong;
                std::cout << "Enter the song you would like to listen to: ";
                std::getline(std::cin, newSong);
                speaker.setSong(newSong);
            }

            std::cout << "The speaker has been updated successfully!\n";
            break;
        }
    }

    if (!deviceFound)
    {
        std::cout << "No Speaker found with the name '" << deviceName << "'. Please check the name and try again.\n";
        return;
    }

    saveSpeakersToFile("Speakers.txt");
}

Speaker* SpeakerManager::findSpeakerByName(const std::string& name)
{
    for (auto& speaker : speakers)
    {
        if (speaker.getName() == name)
        {
            return &speaker;
        }
    }
    return nullptr;
}

void SpeakerManager::syncWithDeviceManager(DeviceManager& manager)
{
    manager.getSpeakers().clear();
    for (const auto& speaker : speakers)
    {
        manager.addDevice(new Speaker(speaker));
    }
}

void SpeakerManager::fetchFromDeviceManager(const DeviceManager& manager)
{
    speakers.clear();
    for (const auto& speaker : manager.getSpeakers())
    {
        speakers.push_back(*speaker);
    }
}
