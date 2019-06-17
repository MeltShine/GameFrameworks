#include "AudioPlayer.h"

namespace meltshine
{
	SoundCache::SoundCache()
	{
	}

	SoundCache::~SoundCache()
	{
		RemoveAllSound();
	}

	void SoundCache::AddSound(std::string key, FMOD::Sound* sound)
	{
		if (HasSound(key) || sound == nullptr)
		{
			return;
		}

		_cached_sound.emplace(key, sound);
	}

	void SoundCache::RemoveSound(const std::string& key)
	{
		auto it = _cached_sound.find(key);
		if (it != _cached_sound.end())
		{
			it->second->release();
			_cached_sound.erase(it);
		}
	}

	void SoundCache::RemoveAllSound()
	{
		for (auto& pair : _cached_sound)
		{
			auto& sound = pair.second;
			if (sound)
			{
				sound->release();
				sound = nullptr;
			}
		}
		_cached_sound.clear();
	}

	bool SoundCache::HasSound(const std::string& key)
	{
		return _cached_sound.find(key) != _cached_sound.end();
	}

	FMOD::Sound* SoundCache::GetSound(const std::string& key) const
	{
		return _cached_sound.at(key);
	}

	AudioPlayer::AudioPlayer()
		: _system(nullptr)
	{
	}

	AudioPlayer::~AudioPlayer()
	{
		if (_system)
		{
			_system->release();
			_system = nullptr;
		}
	}

	bool AudioPlayer::Init(size_t max_channels, FMOD_INITFLAGS init_flags)
	{
		FMOD_RESULT res = FMOD::System_Create(&_system);
		if (res != FMOD_OK)
		{
			return false;
		}

		res = _system->init(max_channels, init_flags, nullptr);
		if (res != FMOD_OK)
		{
			return false;
		}

		_channels.resize(max_channels);
		return true;
	}

	bool AudioPlayer::CreateSound(const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* exinfo, FMOD::Sound** sound)
	{
		FMOD_RESULT res = _system->createSound(name_or_data, mode, exinfo, sound);
		return res == FMOD_OK;
	}

	void AudioPlayer::PlaySound(FMOD::Sound* sound, FMOD_MODE mode, const size_t& channel)
	{
		_system->playSound(sound, 0, false, _channels.size() < channel ? 0 : &_channels[channel]);
	}

	void AudioPlayer::Update()
	{
		_system->update();
	}

	FMOD::Channel* AudioPlayer::GetChannel(const size_t& index) const
	{
		return _channels.size() < index ? _channels[index] : nullptr;
	}

}