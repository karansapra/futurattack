#include "CJAudioEngine.h"

int main()
{
	CJAudioEngine * audio_engine = CJAudioEngine::GetInstance();
	audio_engine->CreateSound("C:\\ogg.ogg");

	system("PAUSE");
}
