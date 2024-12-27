#ifndef PLUG_H
#define PLUG_H

#include "Device.h"
#include <string>

class Plug : public Device // connection to device for shared functions //
{
private:
    bool isOn;
    double live, historic;

public:
    Plug(const std::string& plugName, bool isPlugOn, double Lusage, double Husage); // constructor for light class //

    inline bool getIsOn() const
    {
        return isOn;
    }

    inline double getLive() const
    {
        return live;
    }

    inline double getHistoric() const // inlined getters and setters //
    {
        return historic;
    }

    inline void setOn(bool on)
    {
        isOn = on;
    }

    inline void setLive(double l)
    {
        live = l;
    }

    inline void setHistoric(double h)
    {
        historic = h;
    }

    void quickView() const override;
    void displayDetails() const override; // overriden display and quick view functions //

    std::string toFileString() const; // serialisaton and deserialisation methods //
    static Plug fromFileString(const std::string& data);

    friend std::ostream& operator<<(std::ostream& os, const Plug& plug); // operator overloading for outputing quick view and display functions //
};

#endif

