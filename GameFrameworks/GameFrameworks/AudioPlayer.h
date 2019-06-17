#ifndef __MELTSHINE_AUDIOPLAYER_H__
#define __MELTSHINE_AUDIOPLAYER_H__
#include <fmod.hpp>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#undef PlaySound

namespace meltshine
{
	class SoundCache
	{
	private:
		SoundCache();
	public:
		~SoundCache();

		void AddSound(std::string key, FMOD::Sound* sound);
		void RemoveSound(const std::string& key);
		void RemoveAllSound();
		bool HasSound(const std::string& key);
		FMOD::Sound* GetSound(const std::string& key) const;
		
	private:
		std::unordered_map<std::string, FMOD::Sound*> _cached_sound;

		friend class AudioPlayer;
	};
	class Core;
	class AudioPlayer
	{
	private:
		AudioPlayer();
	public:
		~AudioPlayer();

		bool Init(size_t max_channels, FMOD_INITFLAGS init_flags);
		bool CreateSound(const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* exinfo, FMOD::Sound** sound);
		void PlaySound(FMOD::Sound* sound, FMOD_MODE mode, const size_t& channel);
		void Update();
		FMOD::Channel* GetChannel(const size_t& index) const;
		std::shared_ptr<SoundCache> GetSoundCache() const { return _sound_cache; };

	private:
		FMOD::System* _system;
		std::vector<FMOD::Channel*> _channels;
		std::shared_ptr<SoundCache> _sound_cache;

		friend class Core;
	};
}
#endif // !__MELTSHINE_AUDIOPLAYER_H__
