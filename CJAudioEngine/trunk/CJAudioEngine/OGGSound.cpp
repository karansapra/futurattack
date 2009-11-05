#include "OGGSound.h"

OGGSound::OGGSound()
{
	_loaded = CreateEvent(NULL,TRUE,FALSE,NULL);
	_state_changed = CreateEvent(NULL,TRUE,FALSE,NULL);
}

OGGSound::~OGGSound(void)
{	
	WaitForSingleObject(_loaded,INFINITE);
	if (_sound_data!=0)
	{	
		EnterCriticalSection(_openal_access);	
		alSourceStop(_source[0]);
		alSourcei(_source[0],AL_BUFFER,0);
		alDeleteBuffers(1,_buffer);
		alDeleteSources(1,_source);		
		LeaveCriticalSection(_openal_access);	
	}
}



bool OGGSound::Load(const char * filename)
{
	if (ov_fopen((char*)filename,&_ogg_file)!=0)
		return false;

	_frequency = _ogg_file.vi->rate;
	_channels = _ogg_file.vi->channels;
	_total_time = ov_time_total(&_ogg_file,-1);

	if (_channels!=2 && _channels!=1)
		return false;

	//Si le fichier audio est trop long, on le refuse
	if (_total_time>5*60)
		return false;

	_sound_data_size = _total_time*_frequency*2*_channels;
	
	/*
		Allocating memory for data storage
	*/
	_sound_data = new char[_sound_data_size];
	

	/*
		Read ogg file completly, and store it in memory, in a thread
	*/
	CreateThread(NULL,NULL,_thread_loading_wrapper,(void*)this,0,NULL);
	CreateThread(NULL,0,_thread_play_pause_stop_wrapper,(void*)this,0,NULL);
	return true;
}

void OGGSound::Play()
{
	_current_playing_state = PLAY;
	SetEvent(_state_changed);
}

void OGGSound::Pause()
{
	_current_playing_state = PAUSE;
	SetEvent(_state_changed);
}

void OGGSound::Stop()
{
	_current_playing_state = STOP;
	SetEvent(_state_changed);
}

DWORD WINAPI OGGSound::_thread_loading_wrapper(void * data)
{
	((OGGSound*)(data))->_thread_loading();
	return 0;
}

void OGGSound::_thread_loading()
{
	int total_byte_reads = 0;
	int bitstream;	

	while (total_byte_reads<_sound_data_size)
		total_byte_reads += ov_read(&_ogg_file,_sound_data+total_byte_reads,_sound_data_size-total_byte_reads,0,2,1,&bitstream);

	EnterCriticalSection(_openal_access);
		alGenBuffers(1,_buffer);
		alGenSources(1,_source);
		if (_channels==2)
			alBufferData(_buffer[0],AL_FORMAT_STEREO16,_sound_data,_sound_data_size,_frequency);
		else
			alBufferData(_buffer[0],AL_FORMAT_MONO16,_sound_data,_sound_data_size,_frequency);
		alSourcei(_source[0],AL_BUFFER,_buffer[0]);
	LeaveCriticalSection(_openal_access);

	ov_clear(&_ogg_file);

	delete[] _sound_data;

	SetEvent(_loaded);
}

DWORD WINAPI OGGSound::_thread_play_pause_stop_wrapper(void * data)
{	
	((OGGSound*)(data))->_thread_play_pause_stop();
	return 0;
}

void OGGSound::_thread_play_pause_stop()
{
	WaitForSingleObject(_loaded,INFINITE);
	while (1)
	{
		WaitForSingleObject(_state_changed,INFINITE);
		ResetEvent(_state_changed);		
		EnterCriticalSection(_openal_access);
		switch (_current_playing_state)
		{
		case PLAY:
			alSourcePlay(_source[0]);
			break;

		case PAUSE:
			alSourcePause(_source[0]);
			break;

		case STOP:
			alSourceStop(_source[0]);
			break;

		default:
			break;
		}
		LeaveCriticalSection(_openal_access);	
	}
}

