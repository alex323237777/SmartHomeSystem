#ifndef THERMOSTATMENU_H
#define THERMOSTATMENU_H

#include "ThermostatManager.h"
#include "RadiatorManager.h"

class ThermostatMenu 
{
public:
    void showThermostatMenu(ThermostatManager& thermostatManager);
    // slighlty different implementation of menu system to allow for cross device method(heating boost) //
};

#endif



