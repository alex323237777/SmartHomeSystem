#ifndef SPEAKER_H
#define SPEAKER_H

#include "Device.h"
#include <string>

class Speaker : public Device // subclass of the base device class //
{
private:
    bool isPlaying;
    double volume; // variables for speaker values //
    std::string song;

public: // constructor for the speaker class //
    Speaker(const std::string& speakerName, bool isSongPlaying, double volumeLevel, const std::string& songName);

    inline bool getIsPlaying() const
    {
        return isPlaying;
    }

    inline double getVolume() const
    {
        return volume;
    }

    inline std::string getSong() const
    {
        return song;
    }

    inline void setPlaying(bool play) // inlined functions for getters and setters //
    {
        isPlaying = play;
    }

    inline void setVolume(double level)
    {
        volume = level;
    }

    inline void setSong(const std::string& track)
    {
        song = track;
    }

    void quickView() const override; // overriden quick view and display functions //
    void displayDetails() const override;

    std::string toFileString() const; // serialisation and deserialisation functions //
    static Speaker fromFileString(const std::string& data);

    friend std::ostream& operator<<(std::ostream& os, const Speaker& speaker); // operator overloading for outputing quick view and display functions //
};

#endif

