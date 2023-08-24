#include "utils/sound_manager.hpp"

SoundManager::SoundManager() {
    // Initialize anything necessary
}

void SoundManager::loadSound(const std::string& soundName, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filePath)) {
        soundBuffers[soundName] = buffer;
    }
}

void SoundManager::playSound(const std::string& soundName) {
    if (soundBuffers.find(soundName) != soundBuffers.end()) {
        sf::Sound sound;
        sound.setBuffer(soundBuffers[soundName]);
        sound.play();
    }
}
