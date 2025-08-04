#include "AudioSystem.h"
#include "../core/StringHelper.h"
#include <fmod_errors.h>
#include <iostream>

namespace gaia{
	bool AudioSystem::CheckFMODRESULT(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
			return false; // Error occurred
		}
		return true; // No error

	}
	bool AudioSystem::Initialize() {
		FMOD_RESULT result = FMOD::System_Create(&m_system);
		if (CheckFMODRESULT(result) == false) return false;

		void* extradriverdata = nullptr;
		result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if(!CheckFMODRESULT(result) == false) return false; // Initialization failed

		return true;
	}
	void AudioSystem::ShutDown() {
		CheckFMODRESULT(m_system->release());

	}
	void AudioSystem::Update() {
		CheckFMODRESULT(m_system->update());

	}

	bool AudioSystem::AddSound(const std::string& filename, const std::string& name) {
		std::string key = (name.empty()) ? filename : name; // Use filename if no name provided
		//key = gaia::tolower(key); // Convert to uppercase for case-insensitive comparison
		//check if key exists in sounds map
		if(m_sounds.find(key) != m_sounds.end()) {
			// Sound with this name already exists
			std::cerr << "Audio System : name already exists " << key << std::endl;
			return false;
		}
		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0,&sound);
		if (CheckFMODRESULT(result) == false) return false;
		
		m_sounds[key] = sound; // Store the sound in the map
		return true; // Sound added successfully
	}

	bool AudioSystem::PlaySound(const std::string& name)
	{
		std::string key = name; // Use the provided name directly
		key = gaia::tolower(key); // Convert to uppercase for case-insensitive comparison

		if(m_sounds.find(key) == m_sounds.end()) {
			std::cerr << "Audio System : Sound not found " << name << std::endl;
			return false; // Sound not found
		}
		FMOD_RESULT result = m_system->playSound(m_sounds[key], nullptr, false, nullptr);
		if (!CheckFMODRESULT(result) == false) return false;

		return true;
	}


}