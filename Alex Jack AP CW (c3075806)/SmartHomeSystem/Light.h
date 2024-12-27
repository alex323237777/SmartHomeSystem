#ifndef LIGHT_H // if header file is not defined //
#define LIGHT_H // define the header file //

#include "Device.h" // include the base device class //
#include <string>

class Light : public Device 
{
private:
    bool isOn;
    double brightness;
    std::string sleepTimer;

public: // constructor to intialise the light class //
    Light(const std::string& lightName, bool isLightOn, double brightnessLevel, const std::string& timer);

    inline bool getIsOn() const // inlined getters and setters for light values //
    {
        return isOn;
    }

    inline double getBrightness() const
    {
        return brightness;
    }

    inline std::string getSleepTimer() const
    {
        return sleepTimer;
    }

    inline void setOn(bool on)
    {
        isOn = on;
    }

    inline void setBrightness(double level)
    {
        brightness = level;
    }

    inline void setSleepTimer(const std::string& timer)
    {
        sleepTimer = timer;
    }

    void quickView() const override; // overides 2 base methods to provide customised logic for the light instances //
    void displayDetails() const override;

    std::string toFileString() const; // serialises the lights state into a string format for saving to a file //
    static Light fromFileString(const std::string& data); // deserialises a string representation to create a light object //

    friend std::ostream& operator<<(std::ostream& os, const Light& light); // operator overloading for outputing quick view and display functions //
};

#endif // ends the file guard //







