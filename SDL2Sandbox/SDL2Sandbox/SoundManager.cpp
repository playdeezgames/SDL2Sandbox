#include "SoundManager.h"
namespace tggd::common
{
	void SoundManager::Finish()
	{
		for (auto& entry : sounds)
		{
			if (entry.second)
			{
				Mix_FreeChunk(entry.second);
				entry.second = nullptr;
			}
		}
		sounds.clear();
	}

	void SoundManager::Add(const std::string& name, const std::string& filename)
	{
		//TODO: what if the sound has already been assigned? answer: LEAK!
		sounds[name] = Mix_LoadWAV(filename.c_str());
	}

	void SoundManager::Play(const std::string& name)
	{
		if (!muted)
		{
			Mix_PlayChannel(-1/*Constants::Utility::ANY_CHANNEL*/, sounds[name], 0/*Constants::Utility::NO_LOOPS*/);
		}
	}

	void SoundManager::SetMuted(bool newValue)
	{
		muted = newValue;
	}

	bool SoundManager::IsMuted() const
	{
		return muted;
	}

}
