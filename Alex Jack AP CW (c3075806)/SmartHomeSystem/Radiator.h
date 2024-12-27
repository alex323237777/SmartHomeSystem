#ifndef RADIATOR_H
#define RADIATOR_H

#include "Device.h"
#include <string>

class Radiator : public Device // subclass of device //
{
private:
    bool isOn;
    double temperature; // variables for radiator values //
    std::string schedule;

public: // constructor for the class //
    Radiator(const std::string& radiatorName, bool radiatorOn, double temperatureLevel, const std::string& radiatorSchedule);

    inline bool getIsOn() const 
    {
        return isOn;
    }

    inline double getTemp() const 
    {
        return temperature;
    }

    inline std::string getSchedule() const 
    {
        return schedule;
    }

    inline void setOn(bool on) // inlined functions for getters and setters //
    {
        isOn = on;
    }

    inline void setTemp(double temp) 
    {
        temperature = temp;
    }

    inline void setSchedule(const std::string& newSchedule) 
    {
        schedule = newSchedule;
    }

    void quickView() const override; // overriden functions for inherited functions //
    void displayDetails() const override;

    std::string toFileString() const; // serialisaton and deserialisation methods //
    static Radiator fromFileString(const std::string& data);

    friend std::ostream& operator<<(std::ostream& os, const Radiator& radiator); // operator overloading for outputing quick view and display functions //
};

#endif


