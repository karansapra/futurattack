#include "OGGSound.h"

OGGSound::OGGSound() : ISound()
{

}

OGGSound::~OGGSound(void)
{
}

bool OGGSound::Load(const char * filename)
{
	if (ov_fopen((char*)filename,&_ogg_file)!=0)
		return false;

	printf("New sound:\n");
	printf("%lf:\n",ov_time_total(&_ogg_file,-1)*44100.0f);

	return true;
}

void OGGSound::Play()
{

}