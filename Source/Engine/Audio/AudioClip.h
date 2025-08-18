#pragma once
#include "Resources/Resource.h"

namespace gaia
{
	class AudioClip : public Resource {
	public:
		AudioClip() = default;
		~AudioClip();

		bool Load(const std::string& filename, class AudioSystem& audioSystem);


	private:

		friend class AudioSystem; // Allow AudioSystem to access private members
		FMOD::Sound* m_sound = nullptr; // Pointer to the FMOD sound object
	};

}