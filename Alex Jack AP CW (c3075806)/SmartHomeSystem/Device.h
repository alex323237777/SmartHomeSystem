#ifndef DEVICE_H  
#define DEVICE_H

#include <string>

class Device 
{
protected:
    std::string name;

public: // explicit ensures that the constructor is only called when specifically requested //
    explicit Device(const std::string& deviceName);
    virtual ~Device(); // virtual destructor ensures destructor behaves correctly in a polymorphic context //

    inline std::string getName() const
    {
        return name; // returns device name, works with all device types //
    }
    virtual void quickView() const = 0; // universal function for quick view, used by all device sub classes //
    virtual void displayDetails() const = 0; // universal function for display device details, used by all device sub classes //
};

#endif





