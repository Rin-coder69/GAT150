#pragma once
#include "Component.h"

namespace gaia {
	class AudioSource : public Component {
	public:
		std::string audioClipName;


	public:
		CLASS_PROTOTYPE(AudioSource)

			void Update(float deltatime) override;

		void Play();
	};
}