#pragma once
#include "..\Common\SoundManager.h"
class OptionManager
{
private:
	tggd::common::SoundManager& soundManager;
	void StartMusicWhenAppropriate();
public:
	OptionManager(tggd::common::SoundManager&);
	void Load();
	void Save();
};

