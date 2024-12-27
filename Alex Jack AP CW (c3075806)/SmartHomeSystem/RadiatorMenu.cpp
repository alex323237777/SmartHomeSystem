#include "RadiatorMenu.h"
#include <iostream>
#include <limits>

void RadiatorMenu::showRadiatorMenu(RadiatorManager& radiatorManager) {
    bool inRadiatorMenu = true;

    radiatorManager.loadRadiatorsFromFile("Radiators.txt");

    while (inRadiatorMenu) {
        std::cout << "\nWelcome to the Radiator management menu, please choose an option below:\n";
        std::cout << "1. Quick View\n";
        std::cout << "2. View all radiators in the system\n";
        std::cout << "3. Add a device\n";
        std::cout << "4. Delete a device\n";
        std::cout << "5. Update a device\n";
        std::cout << "9. Exit\n";
        std::cout << "Please select an option: ";

        int choice;
        while (true) {
            std::cin >> choice;
            if (std::cin.fail() || (choice < 1 || (choice > 5 && choice != 9))) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please enter a valid number between 1 and 5, or 9 to exit: ";
                continue;
            }
            break;
        }

        switch (choice) {
        case 1:
            std::cout << "Quick view of a radiator:\n";
            radiatorManager.quickview();
            break;

        case 2:
            radiatorManager.displayRadiators();
            break;

        case 3:
            std::cout << "Adding a new radiator to the system:\n";
            radiatorManager.addRadiator();
            break;

        case 4:
            radiatorManager.deleteRadiator();
            break;

        case 5:
            radiatorManager.updateRadiator();
            break;

        case 9:
            std::cout << "Saving radiators to file and exiting...\n";
            inRadiatorMenu = false;
            break;

        default:
            std::cout << "Invalid choice, please try again.\n";
            break;
        }
    }
}

