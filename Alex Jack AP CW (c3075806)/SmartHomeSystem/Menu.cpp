#include "Menu.h"
#include <iostream>
#include <limits> // allows for numeric limits validation check //

using namespace std;

Menu::Menu() : isRunning(true) {} // Constructor to initialize the menu //

void Menu::displayWelcomeMenu() const { // Outputs the welcome menu //
    cout << "\nWelcome to the Smart Home System\n";
    cout << "Please choose a device type to manage:\n";
    cout << "1. Lights\n";
    cout << "2. Temperature & Humidity Sensors\n";
    cout << "3. Speakers\n";
    cout << "4. Heating Thermostat\n";
    cout << "5. Plugs\n";
    cout << "6. Radiator Valve\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

void Menu::handleChoice(int choice) {
    static RadiatorManager radiatorManager; // creates appropriate instances to allow the heating boost function to work //
    static ThermostatManager thermostatManager(&radiatorManager);

    switch (choice)
    {
    case 1:
    {
        LightMenu lightmenu;
        lightmenu.showLightMenu(); // Navigates to the light menu //
        break;
    }
    case 2:
    {
        TempMenu tempmenu;
        tempmenu.showTempMenu(); // Navigates to the temperature and humidity menu //
        break;
    }
    case 3:
    {
        SpeakerMenu speakermenu;
        speakermenu.showSpeakerMenu(); // Navigates to the speaker menu //
        break;
    }
    case 4:
    {
        ThermostatMenu thermostatmenu;
        thermostatmenu.showThermostatMenu(thermostatManager); // Navigates to the thermostat menu //
        break;
    }
    case 5:
    {
        SocketMenu socketmenu;
        socketmenu.showSocketMenu(); // Navigates to the socket and plug menu //
        break;
    }
    case 6:
    {
        RadiatorMenu radiatormenu;
        radiatormenu.showRadiatorMenu(radiatorManager); // Navigates to the radiator menu //
        break;
    }
    case 9:
        cout << "Exiting... Goodbye!\n";
        isRunning = false; // Stops the menu loop //
        break;

    default:
        cout << "Invalid choice, please try again.\n"; // default response for incorrect entries //
        break;
    }
}

void Menu::run() { // Starts the menu loop //
    int choice;

    do
    {
        displayWelcomeMenu();
        while (true)
        {
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // error handling for if anything other than an integer value is entered //
                cout << "Invalid input, please enter a number between 1 and 9: ";
                continue;
            }

            if (choice < 1 || choice > 9) // error handling for if a number that is too large is entered //
            {
                cout << "Invalid choice, please enter a number between 1 and 9: ";
                continue;
            }

            break;
        }

        handleChoice(choice);

    } while (isRunning);
}

