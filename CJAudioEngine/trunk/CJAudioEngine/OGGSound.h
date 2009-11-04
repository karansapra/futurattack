#pragma once

#include "ISound.h"

class OGGSound :
	public ISound
{
	OggVorbis_File _ogg_file;

public:
	OGGSound();
	virtual ~OGGSound(void);

	bool Load(const char * filename);
	void Play();
};
