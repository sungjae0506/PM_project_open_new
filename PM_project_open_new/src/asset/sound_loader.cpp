#include "sound_loader.h"

FMOD::System* pSystem;

SoundContainer::SoundContainer() {
    FMOD::System_Create(&pSystem);
    pSystem->init(4, FMOD_INIT_NORMAL, NULL);
}

SoundContainer::~SoundContainer() {
    pSystem->release();
}

void SoundContainer::addsound(const char* path) {
    pSystem->createSound(path, FMOD_DEFAULT, NULL, &pSound);
}

void SoundContainer::playsound() {
    pSystem->playSound(pSound, 0, false, pChannel);
}

bool SoundContainer::isplaying() {
    if (pChannel != nullptr) { // ä���� ��ȿ���� Ȯ��
        bool play = false;
        FMOD_RESULT result = pChannel[0]->isPlaying(&play);
        if (result == FMOD_OK && play) { // ��� ������ Ȯ��
            return true;
        }
    }
    return false;
}

bool SoundContainer::soundidleupdate() {
    FMOD_RESULT result = pSystem->update();
    if (result == FMOD_OK) return true;
    return false;
}
