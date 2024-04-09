#pragma once

#include "dll.h"

#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/sndfile.h>

#include "Refl/refl.hpp"
#include "component.h"

class GOLEM_ENGINE_API Audio : public Component
{
public:
    Audio();
    Audio(std::string _fileName, bool _isLooping = false);
    ~Audio();
    
    std::string musicPath;
    ALuint source;
    ALuint buffer;

    bool LoadAudioResource(const char* _fileName, std::vector<char>& _data, ALenum& _format, ALsizei& _frequency);
    bool SetUpAudio();
    void SetLoop(bool _isLooping);
    void SetVolume(int _volume);
    void StopMusic(bool _isPlaying);
    void CleanUp();
    void Play();
    void CheckAudioState();

    void Update() override;

private:
    bool m_isInit = false;
    int m_volume;
    bool m_isLooping = false;
    bool m_isPlaying;
    std::thread m_thread;

    friend refl_impl::metadata::type_info__<Audio>;
};

REFL_AUTO(
    type(Audio),
    field(m_volume)
)