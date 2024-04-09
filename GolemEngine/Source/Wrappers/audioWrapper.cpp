#include "Wrappers/audioWrapper.h"

AudioWrapper::AudioWrapper()
{
}

AudioWrapper::~AudioWrapper()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

AudioWrapper& AudioWrapper::GetInstance()
{
	static AudioWrapper audioWrapper;
	return audioWrapper;
}

bool AudioWrapper::InitDevice()
{
    device = alcOpenDevice(nullptr);
    if (!device)
    {
        std::cerr << "Failed to open OpenAL device" << std::endl;
        return false;
    }

    context = alcCreateContext(device, nullptr);
    if (!context)
    {
        std::cerr << "Failed to create OpenAL context" << std::endl;
        return false;
    }

    alcMakeContextCurrent(context);

    return true;
}
