#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

namespace gaia {
	class AudioSystem {
	public:
		AudioSystem() = default;
		bool Initialize();
		void ShutDown();
		void Update();

		bool AddSound(const std::string& filename, const std::string& name = "");
		bool PlaySound(const std::string& name);

	private:
		bool CheckFMODRESULT(FMOD_RESULT result);

	private:
		FMOD::System* m_system = nullptr;// Pointer to the FMOD system
		std::map<std::string, FMOD::Sound*> m_sounds; // Map to store sounds by name
	};
}
