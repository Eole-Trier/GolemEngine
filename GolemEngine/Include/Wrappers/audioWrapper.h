#pragma once

#include "dll.h"

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/sndfile.h>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Components/audio.h"

class GOLEM_ENGINE_API AudioWrapper
{
public:
    static AudioWrapper& GetInstance();

    bool InitDevice();

    ALCdevice* device;
    ALCcontext* context;

private:
    AudioWrapper();
    ~AudioWrapper();
    AudioWrapper(const AudioWrapper& single) = delete; // Can not copy this class

    const AudioWrapper& operator=(const AudioWrapper& single) = delete;
};