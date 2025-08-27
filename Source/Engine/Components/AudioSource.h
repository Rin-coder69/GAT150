#pragma once
#include "Component.h"

namespace gaia {
	class AudioSource : public Component {
	public:
		std::string audioClipName;


	public:
		std::string audioClipName;
	public:

		Class_PROTOTYPE(AudioSource)

		void Update(float deltatime) override;
		void Play();
	};
}