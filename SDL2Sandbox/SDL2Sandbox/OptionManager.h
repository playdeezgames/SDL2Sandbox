#pragma once
#include "..\..\..\CommonCpp\SoundManager.h"
class OptionManager
{
private:
	tggd::common::SoundManager& soundManager;
public:
	OptionManager(tggd::common::SoundManager&);
	void Load();
	void Save();
};

