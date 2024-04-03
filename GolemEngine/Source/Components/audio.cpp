#include <iostream>

#include "Components/audio.h"
#include "Resource/resourceManager.h"
#include "Resource/tools.h"
#include "Wrappers/windowWrapper.h"
#include "SFML/Audio.hpp"

void Audio::PlayMusic(const std::string& _fileName)
{
	musicPath = Tools::FindFile(_fileName);
	isPlaying = true;

	sf::Music music;
	if (!music.openFromFile(musicPath))
	{
		std::cerr << "Failed to load audio file" << std::endl;
	}

	music.setLoop(true);
	music.play();

	while (music.getStatus() == sf::SoundSource::Playing && isPlaying) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Audio::PlaySound(const std::string& _fileName)
{
	musicPath = Tools::FindFile(_fileName);
	isPlaying = true;

	sf::SoundBuffer buffer;
	sf::Sound sound;

	if (!buffer.loadFromFile(musicPath))
	{
		std::cerr << "Failed to load audio file" << std::endl;
	}

	sound.setBuffer(buffer);
	//sound.setLoop(true);
	sound.play();

	while (sound.getStatus() == sf::SoundSource::Playing && isPlaying) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Audio::StopMusic()
{
	if (WindowWrapper::ShouldWindowClose(WindowWrapper::window))
	{
		isPlaying = false;
		audioThread.join();
	}
}