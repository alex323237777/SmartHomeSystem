#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "Device.h"
#include <string>

class Thermostat : public Device // subclass of base device class //
{
private:
    bool isOn; // values for isOn and schedule //
    std::string schedule;

public: // constructor for the thermostat class //
    Thermostat(const std::string& thermostatName, bool thermostatOn, const std::string& thermostatSchedule);

    inline bool getIsOn() const 
    {
        return isOn;
    }

    inline std::string getSchedule() const 
    {
        return schedule;
    }

    inline void setOn(bool on) // inlined getters and setters //
    {
        isOn = on;
    }

    inline void setSchedule(const std::string& newSchedule) 
    {
        schedule = newSchedule;
    }

    void activateHeatingBoost(); // method to call the heating boost for the radiators in the thermostat menu //

    void quickView() const override; // overidden quick view and display details functions //
    void displayDetails() const override;

    std::string toFileString() const; // serialisaton and deserialisation methods //
    static Thermostat fromFileString(const std::string& data);

    friend std::ostream& operator<<(std::ostream& os, const Thermostat& thermostat); // operator overloading for outputing quick view and display functions //
};

#endif

