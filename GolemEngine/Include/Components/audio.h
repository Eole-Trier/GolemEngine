#pragma once

#include "dll.h"

#include "SFML/Audio.hpp"

#include <string>
#include <iostream>
#include <thread>

//#include <SFML/Audio.hpp>

class GOLEM_ENGINE_API Audio
{
public:
    Audio() {}

    ~Audio() {}

    void PlayMusic(const std::string& _fileName);

    void PlaySound(const std::string& _fileName);
    
    void SetVolume(int _volume);

    void StopMusic();

    bool isPlaying;

    std::string musicPath;

    std::thread audioThread;

private:
};