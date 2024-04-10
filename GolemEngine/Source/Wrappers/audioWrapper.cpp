#include "Wrappers/audioWrapper.h"
#include "golemEngine.h"

void AudioWrapper::UpdatePosition()
{
    listenerPos[0] = GolemEngine::GetCamera()->m_position.x;
    listenerPos[1] = GolemEngine::GetCamera()->m_position.y;
    listenerPos[2] = GolemEngine::GetCamera()->m_position.z;
    alListenerfv(AL_POSITION, listenerPos);
    alListenerfv(AL_VELOCITY, listenerVel);
}

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
