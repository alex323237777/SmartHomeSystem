#include "Speaker.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Speaker::Speaker(const std::string& speakerName, bool isSongPlaying, double volumeLevel, const std::string& songName)
	: Device(speakerName), isPlaying(isSongPlaying), volume(volumeLevel), song(songName) {}

void Speaker::quickView() const
{
	std::cout << *this;
}

void Speaker::displayDetails() const
{
	std::cout << *this;
}

std::string Speaker::toFileString() const
{
	std::ostringstream ss;
	ss << name << "," << isPlaying << "," << volume << "," << song;
	return ss.str();
}

Speaker Speaker::fromFileString(const std::string& data)
{
	std::istringstream ss(data);
	std::string name, song;
	bool isPlaying;
	double volume;

	std::getline(ss, name, ',');
	ss >> isPlaying;
	ss.ignore();
	ss >> volume;
	ss.ignore();
	std::getline(ss, song);

	return Speaker(name, isPlaying, volume, song);
}

std::ostream& operator<<(std::ostream& os, const Speaker& speaker)
{
	os << "\nSpeaker: " << speaker.name << "\nStatus: " << (speaker.isPlaying ? "Playing" : "Paused") << "\nVolume Level: " << speaker.volume << "\nSong Name: " << speaker.song << "\n";
	return os;
}
