#include "SoundManager.h"
namespace tggd::common
{
	void SoundManager::Finish()
	{
		Mix_HaltMusic();
		for (auto& entry : sounds)
		{
			if (entry.second)
			{
				Mix_FreeChunk(entry.second);
				entry.second = nullptr;
			}
		}
		sounds.clear();
		for (auto& entry : music)
		{
			if (entry.second)
			{
				Mix_FreeMusic(entry.second);
				entry.second = nullptr;
			}
		}
		music.clear();

	}

	void SoundManager::AddSound(const std::string& name, const std::string& filename)
	{
		sounds[name] = Mix_LoadWAV(filename.c_str());
	}

	void SoundManager::AddMusic(const std::string& name, const std::string& filename)
	{
		music[name] = Mix_LoadMUS(filename.c_str());
	}

	void SoundManager::PlaySound(const std::string& name) const
	{
		if (!muted)
		{
			const auto& item = sounds.find(name);
			Mix_PlayChannel(-1/*Constants::Utility::ANY_CHANNEL*/, item->second , 0/*Constants::Utility::NO_LOOPS*/);
		}
	}

	void SoundManager::PlayMusic(const std::string& name) const
	{
		if (!muted)
		{
			const auto& item = music.find(name);
			Mix_PlayMusic(item->second, -1);//loop forever
		}
	}

	void SoundManager::SetMuted(bool newValue)
	{
		muted = newValue;
		if (muted)
		{
			Mix_HaltMusic();
		}
	}

	bool SoundManager::IsMuted() const
	{
		return muted;
	}

}
