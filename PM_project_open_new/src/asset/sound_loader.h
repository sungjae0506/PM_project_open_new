#pragma once
#include "inc/fmod.h"
#include "inc/fmod.hpp"
#include <iostream>
#include <conio.h>

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f


class Sound {
public:
	Sound(const char* path, bool loop);
	~Sound();
	FMOD::System* system;
	FMOD::Channel* channel;

	FMOD::Sound* soundfile;
	
	void initsound(bool run);
	void updatesound();
	void playsound();
	void pausesound();
	void resumesound();
	void releasesound();

	const char* path;
	bool loop;

	unsigned int version;
	void* extradriverdata;

	static FMOD_SYSTEM* g_sound_system;
	FMOD_SOUND* m_sound;
	FMOD_CHANNEL* m_channel;

	float m_volume;
	FMOD_BOOL m_bool;
	FMOD_RESULT result;
};