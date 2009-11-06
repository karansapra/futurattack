#pragma once

#ifdef DLL_MAKE
	#define DLL_LOAD __declspec(dllexport)
#else
	#define DLL_LOAD __declspec(dllimport)
#endif


#define REFRESH_RATE		200
#define MAX_SOUNDS			128

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//OpenAL
#include <al.h>
#include <alc.h>
#include <alut.h>

//OggVorbis
#include "vorbis/vorbisfile.h"


