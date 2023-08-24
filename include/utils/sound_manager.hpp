#pragma once
#include <SFML/Audio.hpp>
#include <map>

class SoundManager {
public:
    SoundManager();
    void loadSound(const std::string& soundName, const std::string& filePath);
    void playSound(const std::string& soundName);
    // Add more functions as needed

private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
};
