#pragma once

#include "inc/fmod.h"
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"
#include <conio.h>

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f


class SoundContainer {
public:
	SoundContainer();
	~SoundContainer();

	int cnt = 0;
	FMOD::System* pSystem;
	FMOD::Sound* pSound[2];
	FMOD::Channel* pChannel[1];


	void playsound(int num);
	void addsound(const char* path);
	bool isplaying(int num);
	bool soundidleupdate();
};