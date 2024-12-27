#include "SpeakerMenu.h"
#include "Speaker.h"
#include <iostream>
#include <limits>

void SpeakerMenu::showSpeakerMenu()
{
    bool inSpeakerMenu = true;
    SpeakerManager speakermanager;

    speakermanager.loadSpeakersFromFile("Speakers.txt");

    while (inSpeakerMenu)
    {
        std::cout << "Welcome to the Speaker management menu, please choose an option below: \n";
        std::cout << "1. Quick View: \n";
        std::cout << "2. View all speakers in the system: \n";
        std::cout << "3. Add a speaker: \n";
        std::cout << "4. Delete a speaker: \n";
        std::cout << "5. Update a speaker: \n";
        std::cout << "9. Exit: \n";
        std::cout << "Please select an option: ";

        int choice;

        while (true)
        {
            std::cin >> choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please enter a number between 1 and 9: ";
                continue;
            }

            if (choice < 1 || (choice > 5 && choice != 9))
            {
                std::cout << "Invalid choice, please enter a number between 1 and 5, or 9 to exit: ";
                continue;
            }

            break;
        }

        switch (choice)
        {
        case 1:
        {
            std::cout << "Welcome to quick view!\n";
            speakermanager.quickview();
            break;
        }

        case 2:
        {
            speakermanager.displaySpeakers();
            break;
        }

        case 3:
        {
            std::cout << "Welcome, here you can add a new speaker to the system: \n";
            speakermanager.addSpeaker();
            break;
        }

        case 4:
        {
            std::cout << "Welcome here you can delete a speaker from the system: \n";
            speakermanager.deleteSpeaker();
            break;
        }
        case 5:
        {
            std::cout << "Welcome here you can update a speaker in the system: \n";
            speakermanager.updateSpeaker();
            break;
        }

        case 9:
        {
            std::cout << "Saving Speakers to file...\n";
            return;
        }

        default:
            std::cout << "Invalid choice, please try again: \n";
            break;
        }
    }
}