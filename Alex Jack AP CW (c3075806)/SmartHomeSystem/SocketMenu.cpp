#include "SocketMenu.h"
#include "Plug.h"
#include <iostream>
#include <limits>

void SocketMenu::showSocketMenu()
{
    bool inPlugMenu = true;
    PlugManager plugmanager;

    plugmanager.loadPlugsFromFile("Plugs.txt");

    while (inPlugMenu)
    {
        std::cout << "Welcome to the Plugs management menu, please choose an option below: \n";
        std::cout << "1. Quick View: \n";
        std::cout << "2. View all plugs in the system: \n";
        std::cout << "3. Add a plug: \n";
        std::cout << "4. Delete a plug: \n";
        std::cout << "5. Update a plug: \n";
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
            plugmanager.quickview();
            break;
        }

        case 2:
        {
            plugmanager.displayPlugs();
            break;
        }

        case 3:
        {
            std::cout << "Welcome, here you can add a new plug to the system: \n";
            plugmanager.addPlug();
            break;
        }

        case 4:
        {
            plugmanager.deletePlug();
            break;
        }
        case 5:
        {
            plugmanager.updatePlug();
            break;
        }

        case 9:
        {
            std::cout << "Saving plugs to file...\n";
            return;
        }

        default:
            std::cout << "Invalid choice, please try again: \n";
            break;
        }
    }
}
