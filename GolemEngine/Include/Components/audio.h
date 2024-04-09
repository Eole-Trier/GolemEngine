#pragma once

#include "dll.h"

#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/sndfile.h>

class GOLEM_ENGINE_API Audio
{
public:
    Audio() {}

    ~Audio() {}

    bool Init();

    bool InitializeAudioDevice();

    bool LoadAudioResource(const char* _fileName, std::vector<char>& _data, ALenum& _format, ALsizei& _frequency);

    bool SetUpAudio();

    void CleanUp();
    
    void StopMusic();

    bool isPlaying;

    std::string musicPath;

    std::thread audioThread;

    ALCdevice* device;
    
    ALCcontext* context;
    
    ALuint source;
    
    ALuint buffer;

private:
};