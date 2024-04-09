#include <iostream>

#include "Components/audio.h"
#include "Resource/resourceManager.h"
#include "Resource/tools.h"
#include "Wrappers/windowWrapper.h"

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/sndfile.h>

bool Audio::Init()
{
    if (!InitializeAudioDevice())
    {
        return false;
    }
    if (!SetUpAudio())
    {
        return false;
    }

    return true;
}

bool Audio::InitializeAudioDevice()
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

bool Audio::LoadAudioResource(const char* _fileName, std::vector<char>& _data, ALenum& _format, ALsizei& _frequency)
{
    // Open the WAV file
    SF_INFO info;
    SNDFILE* file = sf_open(_fileName, SFM_READ, &info);
    if (!file) 
    {
        std::cerr << "Failed to open WAV file: " << _fileName << std::endl;
        return false;
    }

    // Check if the file format is supported
    if (info.channels != 1 && info.channels != 2) 
    {
        std::cerr << "Unsupported number of channels: " << info.channels << std::endl;
        sf_close(file);
        return false;
    }

    // Determine the OpenAL format based on the number of channels
    _format = (info.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

    // Read the audio data into memory
    const sf_count_t frameCount = info.frames * info.channels;
    _data.resize(frameCount * sizeof(short));
    const sf_count_t readCount = sf_read_short(file, reinterpret_cast<short*>(_data.data()), frameCount);
    if (readCount != frameCount) 
    {
        std::cerr << "Failed to read WAV file data" << std::endl;
        sf_close(file);
        return false;
    }

    // Set the frequency
    _frequency = info.samplerate;

    // Close the file
    sf_close(file);

    return true;
}

bool Audio::SetUpAudio()
{
    alGenBuffers(1, &buffer);

    std::vector<char> data;
    ALenum format;
    ALsizei frequency;

    if (!LoadAudioResource(Tools::FindFile("music_01.wav").c_str(), data, format, frequency))
    {
        std::cerr << "Failed to load WAV file" << std::endl;
        return false;
    }

    alBufferData(buffer, format, &data[0], static_cast<ALsizei>(data.size()), frequency);

    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    return true;
}

void Audio::CleanUp()
{
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void Audio::StopMusic()
{
	if (WindowWrapper::ShouldWindowClose(WindowWrapper::window))
	{
		isPlaying = false;
		audioThread.join();
	}
}