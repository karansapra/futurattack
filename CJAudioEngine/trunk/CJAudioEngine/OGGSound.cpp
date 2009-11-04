#include "OGGSound.h"

OGGSound::OGGSound() : ISound()
{

}

OGGSound::~OGGSound(void)
{	
	if (_sound_data!=0)
	{
		alSourceStop(_source[0]);
		alSourcei(_source[0],AL_BUFFER,0);
		alDeleteBuffers(1,_buffer);
		alDeleteSources(1,_source);
		delete[] _sound_data;
	}
}

bool OGGSound::Load(const char * filename)
{
	if (ov_fopen((char*)filename,&_ogg_file)!=0)
		return false;

	printf("New sound:\n");

	_frequency = _ogg_file.vi->rate;
	_channels = _ogg_file.vi->channels;
	_total_time = ov_time_total(&_ogg_file,-1);

	//Si le fichier audio est trop long, on le refuse
	if (_total_time>5*60)
		return false;

	_sound_data_size = _total_time*_frequency*2*_channels;
	
	/*
		Allocating memory for data storage
	*/
	_sound_data = new char[_sound_data_size];
	
	int total_byte_reads = 0;
	int bitstream;	

	/*
		Read ogg file completly, and store it in memory
	*/
	while (total_byte_reads<_sound_data_size)
		total_byte_reads += ov_read(&_ogg_file,_sound_data+total_byte_reads,_sound_data_size-total_byte_reads,0,2,1,&bitstream);

	ov_clear(&_ogg_file);

	alGenBuffers(1,_buffer);
	alGenSources(1,_source);

	alBufferData(_buffer[0],AL_FORMAT_STEREO16,_sound_data,_sound_data_size,_frequency);
	alSourcei(_source[0],AL_BUFFER,_buffer[0]);

	return true;
}

void OGGSound::Play()
{
	alSourcePlay(_source[0]);
}