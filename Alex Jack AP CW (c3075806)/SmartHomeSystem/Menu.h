#ifndef MENU_H
#define MENU_H

#include "LightMenu.h"
#include "TempMenu.h"
#include "SocketMenu.h"
#include "LightMenu.h"
#include "TempMenu.h" // includes all device type headers //
#include "SpeakerMenu.h"
#include "ThermostatMenu.h"
#include "SocketMenu.h"
#include "RadiatorMenu.h"
#include "ThermostatManager.h"
#include "RadiatorManager.h"


class Menu 
{
private:
    bool isRunning; // Controls the menu loop //

    void displayWelcomeMenu() const;
    void handleChoice(int choice);

public:
    Menu(); // Constructor to initialize the menu //
    void run(); // Starts the menu loop //
};

#endif
