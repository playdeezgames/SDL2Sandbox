#include "OptionManager.h"
#include "..\Constants\Options.h"
#include "..\Constants\Sound.h"
typedef struct
{
	bool muted;
	int sfxVolume;
	int muxVolume;
} GameOptions;

OptionManager::OptionManager(tggd::common::SoundManager& sndMan)
	: soundManager(sndMan)
{

}

void OptionManager::Load()
{
	FILE* f = nullptr;
	fopen_s(&f, Constants::Options::FILE_NAME.c_str(), Constants::Options::READ_MODE.c_str());
	if (f)
	{
		GameOptions options;
		fseek(f, 0, SEEK_END);//seek to end of file to determine position
		if (ftell(f) == sizeof(GameOptions))
		{
			fseek(f, 0, SEEK_SET);//reset to start of file for reading
			fread(&options, sizeof(GameOptions), Constants::Options::RECORD_COUNT, f);
			soundManager.SetMuted(options.muted);
		}
		fclose(f);
	}
	StartMusicWhenAppropriate();
}

void OptionManager::Save()
{
	remove(Constants::Options::FILE_NAME.c_str());
	FILE* f = nullptr;
	fopen_s(&f, Constants::Options::FILE_NAME.c_str(), Constants::Options::WRITE_MODE.c_str());
	if (f)
	{
		GameOptions options = { 0 };
		options.muted = soundManager.IsMuted();
		fwrite(&options, sizeof(GameOptions), Constants::Options::RECORD_COUNT, f);
		fclose(f);
	}
	StartMusicWhenAppropriate();
}

void OptionManager::StartMusicWhenAppropriate()
{
	if (!soundManager.IsMuted())
	{
		soundManager.PlayMusic(Constants::Sound::Name::SONG);
	}
	else
	{
		Mix_HaltMusic();
	}
}