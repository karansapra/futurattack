#pragma once

#include "CJAudioEngineSystem.h"

class ISound
{
	char * _sound_data;
	bool _loaded_correctly;
	ALuint _buffer[1];
	ALuint _source[1];

public:
	ISound(void);
	virtual ~ISound(void);

	virtual bool Load(const char * filename)=0;
	virtual void Play()=0;
};
