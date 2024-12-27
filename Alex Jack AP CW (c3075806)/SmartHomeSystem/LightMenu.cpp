#include "LightMenu.h"
#include "Light.h"
#include <iostream>
#include <limits>

void LightMenu::showLightMenu() // calls show menu function to display the menu //
{
    bool inLightMenu = true;
    LightManager lightmanager;
    // creates instance of light manager to call each options function //
    lightmanager.loadLightsFromFile("Devices.txt");
    // loads the values from the text file into the object //
    while (inLightMenu)
    {
        std::cout << "Welcome to the Lights management menu, please choose an option below: \n";
        std::cout << "1. Quick View: \n";
        std::cout << "2. View all lights in the system: \n";
        std::cout << "3. Add a device: \n";
        std::cout << "4. Delete a device: \n";
        std::cout << "5. Update a device: \n";
        std::cout << "9. Exit: \n";
        std::cout << "Please select an option: ";

        int choice;

        while (true) 
        {
            std::cin >> choice;

            if (std::cin.fail()) 
            {
                std::cin.clear(); // checks if the input is in the correct format //
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input, please enter a number between 1 and 9: ";
                continue; 
            }

            if (choice < 1 || (choice > 5 && choice != 9)) 
            { // checks if the choice is a valid number //
                std::cout << "Invalid choice, please enter a number between 1 and 5, or 9 to exit: ";
                continue; 
            }

            break;
        }

        switch (choice)
        { // switch case to call each function when appropriate //
        case 1:
        {
            std::cout << "Welcome to quick view!\n";
            lightmanager.quickview();
            break;
        }

        case 2:
        {
            lightmanager.displayLights();
            break;
        }

        case 3:
        {
            std::cout << "Welcome, here you can add a new light to the system: \n";
            lightmanager.addLight();
            break;
        }

        case 4:
        {
            lightmanager.deleteLight();
            break;
        }
        case 5:
        {
            lightmanager.updateLight();
            break;
        }

        case 9:
        {
            std::cout << "Saving lights to file...\n";
            return; 
        }

        default:
            std::cout << "Invalid choice, please try again: \n";
            break; // error message if invalid choice is input //
        }
    }
}

