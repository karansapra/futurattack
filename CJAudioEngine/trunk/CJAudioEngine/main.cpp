#include "CJAudioEngine.h"

int main()
{
	CJAudioEngine * audio_engine = CJAudioEngine::GetInstance();
	
	ISound * music = audio_engine->CreateSound("C:\\ogg.ogg");

	if (music!=0)
		music->Play();	
	

	system("PAUSE");
	if (music!=0)
		delete music;
}
