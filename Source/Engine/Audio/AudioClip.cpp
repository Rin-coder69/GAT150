#include "AudioClip.h"
#include "Audio/AudioClip.h"
#include "AudioSystem.h"

namespace gaia
{
    AudioClip::~AudioClip() {
		m_sound->release(); // Release the sound resource

    }

    bool gaia::AudioClip::Load(const std::string& filename, AudioSystem& audioSystem)
    {
        FMOD_RESULT result = audioSystem.m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &m_sound);
        if (!AudioSystem::CheckFMODRESULT(result)) return false;
        return true;
    }
}