#pragma once

#include "dll.h"

#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <vector3.h>
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
    void SetPositon();
    void CleanUp();
    void Play();

    void Update() override;

private:
    bool m_isInit = false;
    float m_volume = 1.0f;
    bool m_isLooping = false;
    bool m_isPlaying;
    std::thread m_thread;
    Vector3 m_position;
    ALfloat m_sourcePos[3] = { 0.0f, 0.0f, 0.0f };
    ALfloat m_sourceVel[3] = { 0.0f, 0.0f, 0.0f };

    friend refl_impl::metadata::type_info__<Audio>;
};

REFL_AUTO(
    type(Audio),
    field(m_volume)
)