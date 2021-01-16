#pragma once
#include <map>
#include <string>
#include <SDL_Mixer.h>
namespace tggd::common
{
	class SoundManager
	{
	private:
		std::map<std::string, Mix_Chunk*> sounds;
		std::map<std::string, Mix_Music*> music;
		bool muted;
		int muxVolume;
		int sfxVolume;
		void FinishMusic();
		void FinishSound();
	public:
		SoundManager();
		void Finish();
		void AddSound(const std::string&, const std::string&);
		void AddMusic(const std::string&, const std::string&);
		void PlaySound(const std::string&) const;
		void PlayMusic(const std::string&) const;
		void SetMuted(bool);
		bool IsMuted() const;
		void SetSfxVolume(int);
		int GetSfxVolume() const;
		void SetMuxVolume(int);
		int GetMuxVolume() const;
	};
}
