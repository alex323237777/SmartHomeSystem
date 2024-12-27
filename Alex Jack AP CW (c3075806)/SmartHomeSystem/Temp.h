#ifndef TEMP_H 
#define TEMP_H 

#include "Device.h"
#include <string>

class Temp : public Device // subclass of base device class //
{
private:
    double temperature, humidity, hisT, hisH;
    // all double values for live and historic temperature and humidity readings //

public: // constructor for the temp class //
    Temp(const std::string& tempName, double temperatureLevel, double humidityLevel, double hisTempL, double hisHumidL);

    inline double getTemp() const
    {
        return temperature;
    }

    inline double getHumid() const
    {
        return humidity;
    }

    inline double getHisT() const
    {
        return hisT;
    }

    inline double getHisH() const // inlined getters and setters //
    {
        return hisH;
    }

    inline void setTemp(double level)
    {
        temperature = level;
    }

    inline void setHumid(double hLevel)
    {
        humidity = hLevel;
    }

    inline void setHisT(double hTLevel)
    {
        hisT = hTLevel;
    }

    inline void setHisH(double hHLevel)
    {
        hisH = hHLevel;
    }

    void quickView() const override; // overriden quick view and display functions //
    void displayDetails() const override;

    std::string toFileString() const; // serialisaton and deserialisation methods //
    static Temp fromFileString(const std::string& data);

    friend std::ostream& operator<<(std::ostream& os, const Temp& temp); // operator overloading for outputing quick view and display functions //
};

#endif
