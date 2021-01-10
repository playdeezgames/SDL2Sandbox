#pragma once
#include <map>
#include <string>
#include "SDL_Mixer.h"
namespace tggd::common
{
	class SoundManager
	{
	private:
		std::map<std::string, Mix_Chunk*> sounds;
	public:
		void Finish();
		void Add(const std::string&, const std::string&);
		void Play(const std::string&);
	};
}
