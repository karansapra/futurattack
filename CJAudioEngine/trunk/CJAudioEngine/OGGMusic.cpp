#include "OGGMusic.h"

OGGMusic::OGGMusic(void)
{
	_state_changed = CreateEvent(NULL,TRUE,FALSE,NULL);
	actual_reads = 0;
	total_reads = 0;
}

OGGMusic::~OGGMusic(void)
{
}

bool OGGMusic::Load(const char * filename)
{
	if (ov_fopen((char*)filename,&_ogg_file)!=0)
		return false;	

	_frequency = _ogg_file.vi->rate;
	_channels = _ogg_file.vi->channels;
	_total_time = ov_time_total(&_ogg_file,-1);

	if (_channels!=2 && _channels!=1)
		return false;

	//On alloue tout le temps pour 1sec de musique
	_stream_block_size = _frequency*2*_channels;
	
	_sound_data_size = _total_time*_frequency*2*_channels;

	_sound_data[0] = new char[_stream_block_size];
	_sound_data[1] = new char[_stream_block_size];

	alGenBuffers(2,_buffer);
	alGenSources(1,_source);

	CreateThread(NULL,NULL,_thread_play_pause_stop_wrapper,(void*)this,0,NULL);	

	return true;
}

void OGGMusic::Play()
{	
	if (_buffer[0]==0)
		return;

	EnterCriticalSection(_openal_access);
	for (int i=0;i<2;i++)
	{	
		while (actual_reads!=_stream_block_size && actual_reads+total_reads<_sound_data_size)
			actual_reads += ov_read(&_ogg_file,_sound_data[i]+actual_reads,_stream_block_size-actual_reads,0,2,1,&bitstream);

		total_reads += actual_reads;

		alBufferData(_buffer[i],AL_FORMAT_STEREO16,_sound_data[i],_stream_block_size,_frequency);
		alSourceQueueBuffers(_source[0],1,&_buffer[i]);

		actual_reads = 0;
	}

	alSourcePlay(_source[0]);
	LeaveCriticalSection(_openal_access);

	_current_playing_state = PLAY;
	SetEvent(_state_changed);
}

void OGGMusic::Pause()
{
	_current_playing_state = PAUSE;
	SetEvent(_state_changed);
}

void OGGMusic::Stop()
{
	_current_playing_state = STOP;
	SetEvent(_state_changed);
}

DWORD WINAPI OGGMusic::_thread_play_pause_stop_wrapper(void * data)
{	
	((OGGMusic*)(data))->_thread_play_pause_stop();
	return 0;
}

void OGGMusic::_thread_play_pause_stop()
{
	total_reads=0;
	actual_reads=0;	
	buffer_unqueue = 0;

	if (_buffer[0]==0)
		return;

	while (1)
	{
		WaitForSingleObject(_state_changed,100);
		ResetEvent(_state_changed);	

		switch (_current_playing_state)
		{
		case PLAY:
			nprocessed = 0;

			EnterCriticalSection(_openal_access);
			alGetSourcei(_source[0],AL_BUFFERS_PROCESSED,&nprocessed);
			//printf("processed:%d",nprocessed);
			for (int i=0;i<nprocessed;i++)
			{	
				buffer_unqueue = 0;
				alSourceUnqueueBuffers(_source[0],1,&buffer_unqueue);
				while (actual_reads!=_stream_block_size && actual_reads+total_reads<_sound_data_size)
					actual_reads += ov_read(&_ogg_file,_sound_data[0]+actual_reads,_stream_block_size-actual_reads,0,2,1,&bitstream);

				total_reads += actual_reads;

				alBufferData(buffer_unqueue,AL_FORMAT_STEREO16,_sound_data[0],_stream_block_size,_frequency);
				alSourceQueueBuffers(_source[0],1,&buffer_unqueue);

				actual_reads = 0;

				ALint sstate;
				alGetSourcei(_source[0],AL_SOURCE_STATE,&sstate);
				if (sstate!=AL_PLAYING)
				{
					ALint nqueue;
					alGetSourcei(_source[0],AL_BUFFERS_QUEUED,&nqueue);
					if (nqueue)
					{
						alSourcePlay(_source[0]);
					} else
					{
						alSourceStop(_source[0]);
						_current_playing_state = STOP;
						SetEvent(_state_changed);
					}
				}
			}
			
			LeaveCriticalSection(_openal_access);
			break;

		case PAUSE:
			EnterCriticalSection(_openal_access);
			alSourcePause(_source[0]);
			LeaveCriticalSection(_openal_access);
			break;

		case STOP:
			break;

		default:
			break;
		}
		
	}
}
