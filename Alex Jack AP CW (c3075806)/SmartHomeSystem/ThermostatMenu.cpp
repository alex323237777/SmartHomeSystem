#include "ThermostatMenu.h"
#include <iostream>
#include <limits>

void ThermostatMenu::showThermostatMenu(ThermostatManager& thermostatManager) {
    bool inThermostatMenu = true;

    thermostatManager.loadThermostatsFromFile("Thermostats.txt");


    while (inThermostatMenu) {
        std::cout << "\nWelcome to the Thermostat management menu, please choose an option below:\n";
        std::cout << "1. Quick View\n";
        std::cout << "2. View all thermostats in the system\n";
        std::cout << "3. Add a device\n";
        std::cout << "4. Delete a device\n";
        std::cout << "5. Update a device\n";
        std::cout << "6. Activate Heating Boost\n";
        std::cout << "9. Exit\n";
        std::cout << "Please select an option: ";

        int choice;
        while (true) {
            std::cin >> choice;
            if (std::cin.fail() || (choice < 1 || (choice > 6 && choice != 9))) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please enter a valid number between 1 and 6, or 9 to exit: ";
                continue;
            }
            break;
        }

        switch (choice) {
        case 1:
            std::cout << "Quick view of a thermostat:\n";
            thermostatManager.quickview();
            break;

        case 2:
            thermostatManager.displayThermostats();
            break;

        case 3:
            std::cout << "Adding a new thermostat to the system:\n";
            thermostatManager.addThermostat();
            break;

        case 4:
            thermostatManager.deleteThermostat();
            break;

        case 5:
            thermostatManager.updateThermostat();
            break;

        case 6:
            std::cout << "Activating Heating Boost for all thermostats and radiators...\n";
            thermostatManager.activateHeatingBoost();
            break;

        case 9:
            std::cout << "Saving thermostats to file and exiting...\n";
            inThermostatMenu = false;
            break;

        default:
            std::cout << "Invalid choice, please try again.\n";
            break;
        }
    }
}

