#include "TempMenu.h"
#include "Temp.h"
#include <iostream>
#include <limits>

void TempMenu::showTempMenu()
{
    bool inTempMenu = true;
    TempManager tempmanager;

    tempmanager.loadTempsFromFile("Temps.txt");

    while (inTempMenu)
    {
        std::cout << "Welcome to the Temparature and Humidity Sensor management menu, please choose an option below: \n";
        std::cout << "1. Quick View: \n";
        std::cout << "2. View all sensors in the system: \n";
        std::cout << "3. Add a sesnor: \n";
        std::cout << "4. Delete a sesnor: \n";
        std::cout << "5. Update a sensor: \n";
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
            tempmanager.quickview();
            break;
        }

        case 2:
        {
            std::cout << "Welcome to the sensor display system: \n";
            tempmanager.displayTemps();
            break;
        }

        case 3:
        {
            std::cout << "Welcome, here you can add a new sensor to the system: \n";
            tempmanager.addTemp();
            break;
        }

        case 4:
        {
            tempmanager.deleteTemp();
            break;
        }
        case 5:
        {
            tempmanager.updateTemp();
            break;
        }

        case 9:
        {
            std::cout << "Saving lights to file...\n";
            return;
        }

        default:
            std::cout << "Invalid choice, please try again: \n";
            break;
        }
    }
}