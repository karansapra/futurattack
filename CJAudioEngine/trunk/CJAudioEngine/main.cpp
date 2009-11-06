#include "CJAudioEngine.h"

int main()
{
	CJAudioEngine * audio_engine = CJAudioEngine::GetInstance();
	IMusic * music = audio_engine->CreateMusic("C:\\sample.ogg");
	
	music->Play();

	char c;
	while ((c=getchar())!='q')
	{
		switch (c)
		{
		case 'p':
			music->Pause();
			break;
		case 's':
			music->Stop();
			break;
		case 'r':
			music->Play();
			break;

		default:
			break;
		}
	}

	if (music!=0)
		delete music;
}
